// WebView2 spike: a native g++ program that hosts a web page and exchanges messages with it.
//
// What it proves:
//   1. g++ can compile against the WebView2 C API header.
//   2. The loader DLL can be called from a g++ build, with no MSVC libraries.
//   3. The page can send a message to C++, and C++ can reply to the page.
//
// The window should show the page. The page sends "page loaded" to C++, and the status line changes to
// "C++ received: page loaded". Clicking the button sends "ping", and the status changes to "C++ received: ping".

#include <windows.h>
#include <objbase.h>
#include <WebView2.h>

#include <string>

namespace {

const wchar_t* kWindowClass = L"WebView2Spike";

// The page shown in the window. Its script listens for replies, and posts messages to C++.
const wchar_t* kPage = LR"HTML(
<!DOCTYPE html>
<html>
<body style="font-family: Segoe UI, sans-serif; margin: 24px; background: #ffffff; color: #1a1a1a;">
  <h1>WebView2 spike</h1>
  <p id="status">Waiting for the C++ side...</p>
  <button id="ping">Send ping</button>
  <script>
    window.chrome.webview.addEventListener('message', (event) => {
      document.getElementById('status').textContent = event.data;
    });
    document.getElementById('ping').addEventListener('click', () => {
      window.chrome.webview.postMessage('ping');
    });
    window.chrome.webview.postMessage('page loaded');
  </script>
</body>
</html>
)HTML";

// The signature of CreateCoreWebView2EnvironmentWithOptions, which the loader DLL exports.
using CreateEnvironmentFn = HRESULT(STDAPICALLTYPE*)(
    PCWSTR browserExecutableFolder,
    PCWSTR userDataFolder,
    ICoreWebView2EnvironmentOptions* options,
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler* handler);

void Fail(const wchar_t* message, HRESULT code) {
    wchar_t hex[16];
    swprintf(hex, 16, L"%08lX", static_cast<unsigned long>(code));
    std::wstring text = std::wstring(message) + L"\n\nError code: 0x" + hex;
    MessageBoxW(nullptr, text.c_str(), L"WebView2 spike", MB_ICONERROR);
}

class Host;

// COM callbacks. WebView2 calls these when work finishes. Each one holds a reference count, and deletes itself
// when the count reaches zero, as the COM rules require.

class EnvironmentHandler final : public ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler {
public:
    explicit EnvironmentHandler(Host& host) : host_(host) {}

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override {
        if (riid == IID_IUnknown ||
            riid == IID_ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler) {
            *object = static_cast<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler*>(this);
            AddRef();
            return S_OK;
        }
        *object = nullptr;
        return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef() override { return ++refs_; }
    ULONG STDMETHODCALLTYPE Release() override {
        ULONG count = --refs_;
        if (count == 0) delete this;
        return count;
    }

    HRESULT STDMETHODCALLTYPE Invoke(HRESULT result, ICoreWebView2Environment* environment) override;

private:
    Host& host_;
    ULONG refs_ = 1;
};

class ControllerHandler final : public ICoreWebView2CreateCoreWebView2ControllerCompletedHandler {
public:
    explicit ControllerHandler(Host& host) : host_(host) {}

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override {
        if (riid == IID_IUnknown ||
            riid == IID_ICoreWebView2CreateCoreWebView2ControllerCompletedHandler) {
            *object = static_cast<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler*>(this);
            AddRef();
            return S_OK;
        }
        *object = nullptr;
        return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef() override { return ++refs_; }
    ULONG STDMETHODCALLTYPE Release() override {
        ULONG count = --refs_;
        if (count == 0) delete this;
        return count;
    }

    HRESULT STDMETHODCALLTYPE Invoke(HRESULT result, ICoreWebView2Controller* controller) override;

private:
    Host& host_;
    ULONG refs_ = 1;
};

class MessageHandler final : public ICoreWebView2WebMessageReceivedEventHandler {
public:
    explicit MessageHandler(Host& host) : host_(host) {}

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override {
        if (riid == IID_IUnknown || riid == IID_ICoreWebView2WebMessageReceivedEventHandler) {
            *object = static_cast<ICoreWebView2WebMessageReceivedEventHandler*>(this);
            AddRef();
            return S_OK;
        }
        *object = nullptr;
        return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef() override { return ++refs_; }
    ULONG STDMETHODCALLTYPE Release() override {
        ULONG count = --refs_;
        if (count == 0) delete this;
        return count;
    }

    HRESULT STDMETHODCALLTYPE Invoke(ICoreWebView2* sender,
                                     ICoreWebView2WebMessageReceivedEventArgs* args) override;

private:
    Host& host_;
    ULONG refs_ = 1;
};

// Owns the WebView2 objects, and drives them from the window's messages.
class Host {
public:
    explicit Host(HWND window) : window_(window) {}
    ~Host() { Release(); }

    Host(const Host&) = delete;
    Host& operator=(const Host&) = delete;

    // Starts the chain: load the loader, create the environment, then the controller, then the page.
    bool Start() {
        HMODULE loader = LoadLibraryW(L"WebView2Loader.dll");
        if (!loader) {
            Fail(L"WebView2Loader.dll wasn't found next to the program.", static_cast<HRESULT>(GetLastError()));
            return false;
        }

        // GetProcAddress returns a generic function pointer. Going through void* keeps g++ from warning about
        // casting between function types, which is safe here because we know the exported signature.
        auto create = reinterpret_cast<CreateEnvironmentFn>(reinterpret_cast<void*>(
            GetProcAddress(loader, "CreateCoreWebView2EnvironmentWithOptions")));
        if (!create) {
            Fail(L"The loader DLL doesn't export CreateCoreWebView2EnvironmentWithOptions.",
                 static_cast<HRESULT>(GetLastError()));
            return false;
        }

        // nullptr for the folders means "use the defaults", which is what a first test needs.
        HRESULT hr = create(nullptr, nullptr, nullptr, new EnvironmentHandler(*this));
        if (FAILED(hr)) {
            Fail(L"WebView2 couldn't start. Is the WebView2 Runtime installed?", hr);
            return false;
        }
        return true;
    }

    HRESULT OnEnvironment(HRESULT result, ICoreWebView2Environment* environment) {
        if (FAILED(result)) {
            Fail(L"The WebView2 environment couldn't be created.", result);
            return result;
        }
        environment_ = environment;
        environment_->AddRef();
        return environment_->CreateCoreWebView2Controller(window_, new ControllerHandler(*this));
    }

    HRESULT OnController(HRESULT result, ICoreWebView2Controller* controller) {
        if (FAILED(result)) {
            Fail(L"The WebView2 controller couldn't be created.", result);
            return result;
        }
        controller_ = controller;
        controller_->AddRef();

        // get_CoreWebView2 hands back a new reference, which Release frees later.
        HRESULT hr = controller_->get_CoreWebView2(&webview_);
        if (FAILED(hr)) {
            Fail(L"The WebView2 control couldn't be reached from the controller.", hr);
            return hr;
        }

        Resize();

        hr = webview_->add_WebMessageReceived(new MessageHandler(*this), &token_);
        if (FAILED(hr)) {
            Fail(L"Couldn't listen for messages from the page.", hr);
            return hr;
        }

        return webview_->NavigateToString(kPage);
    }

    HRESULT OnMessage(ICoreWebView2WebMessageReceivedEventArgs* args) {
        LPWSTR message = nullptr;
        HRESULT hr = args->TryGetWebMessageAsString(&message);
        if (SUCCEEDED(hr) && message) {
            std::wstring reply = std::wstring(L"C++ received: ") + message;
            CoTaskMemFree(message);
            return webview_->PostWebMessageAsString(reply.c_str());
        }
        return hr;
    }

    // Keeps the page the same size as the window.
    void Resize() {
        if (!controller_) return;
        RECT bounds{};
        GetClientRect(window_, &bounds);
        controller_->put_Bounds(bounds);
    }

private:
    void Release() {
        if (webview_) {
            webview_->Release();
            webview_ = nullptr;
        }
        if (controller_) {
            controller_->Release();
            controller_ = nullptr;
        }
        if (environment_) {
            environment_->Release();
            environment_ = nullptr;
        }
    }

    HWND window_;
    ICoreWebView2Environment* environment_ = nullptr;
    ICoreWebView2Controller* controller_ = nullptr;
    ICoreWebView2* webview_ = nullptr;
    EventRegistrationToken token_{};
};

// The COM callbacks forward to Host. They're defined after Host, so Host's methods are visible here.

HRESULT STDMETHODCALLTYPE EnvironmentHandler::Invoke(HRESULT result, ICoreWebView2Environment* environment) {
    return host_.OnEnvironment(result, environment);
}

HRESULT STDMETHODCALLTYPE ControllerHandler::Invoke(HRESULT result, ICoreWebView2Controller* controller) {
    return host_.OnController(result, controller);
}

HRESULT STDMETHODCALLTYPE MessageHandler::Invoke(ICoreWebView2* sender,
                                                 ICoreWebView2WebMessageReceivedEventArgs* args) {
    (void)sender;
    return host_.OnMessage(args);
}

Host* g_host = nullptr;

LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
        case WM_SIZE:
            if (g_host) g_host->Resize();
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcW(window, message, wparam, lparam);
    }
}

}  // namespace

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE /*previous*/, PWSTR /*command_line*/, int show) {
    // WebView2 needs a single-threaded apartment, because its events arrive on the window's thread.
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        Fail(L"COM couldn't start.", hr);
        return 1;
    }

    WNDCLASSW window_class{};
    window_class.lpfnWndProc = WndProc;
    window_class.hInstance = instance;
    window_class.lpszClassName = kWindowClass;
    window_class.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassW(&window_class);

    HWND window = CreateWindowExW(0, kWindowClass, L"WebView2 spike", WS_OVERLAPPEDWINDOW,
                                  CW_USEDEFAULT, CW_USEDEFAULT, 900, 600,
                                  nullptr, nullptr, instance, nullptr);
    if (!window) {
        Fail(L"The window couldn't be created.", static_cast<HRESULT>(GetLastError()));
        CoUninitialize();
        return 1;
    }
    ShowWindow(window, show);
    UpdateWindow(window);

    int exit_code = 0;
    {
        // Scoped so the host releases its WebView2 objects before COM shuts down.
        Host host(window);
        g_host = &host;
        if (host.Start()) {
            MSG msg{};
            while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
            exit_code = static_cast<int>(msg.wParam);
        } else {
            exit_code = 1;
        }
        g_host = nullptr;
    }

    CoUninitialize();
    return exit_code;
}
