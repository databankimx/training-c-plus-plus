// app.cpp: the lesson runner's windows. The main window hosts the front end (from lesson-runner\web). The pop-out
// lesson window hosts the same web folder's lesson page. The page's commands come in as web messages, and the
// router's replies and events go back out.
//
// Both pages are served from a virtual address, https://runner.local/, mapped to the web folder. Modules and
// relative imports only load from a real web address, which is why NavigateToString is not used.

#include "discovery.hpp"
#include "router.hpp"
#include "runner.hpp"

#include <windows.h>
#include <objbase.h>
#include <WebView2.h>

#include <filesystem>
#include <memory>
#include <string>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace {

const wchar_t* kWindowClass = L"LessonRunner";
const wchar_t* kLessonWindowClass = L"LessonRunnerLesson";
const wchar_t* kVirtualHost = L"runner.local";
const wchar_t* kStartPage = L"https://runner.local/index.html";
const wchar_t* kLessonPage = L"https://runner.local/lesson.html";

using CreateEnvironmentFn = HRESULT(STDAPICALLTYPE*)(
    PCWSTR browserExecutableFolder,
    PCWSTR userDataFolder,
    ICoreWebView2EnvironmentOptions* options,
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler* handler);

void Fail(const wchar_t* message, HRESULT code) {
    wchar_t hex[16];
    swprintf(hex, 16, L"%08lX", static_cast<unsigned long>(code));
    std::wstring text = std::wstring(message) + L"\n\nError code: 0x" + hex;
    MessageBoxW(nullptr, text.c_str(), L"Lesson Runner", MB_ICONERROR);
}

std::wstring utf8_to_wide(const std::string& text) {
    if (text.empty()) return {};
    const int size = MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), nullptr, 0);
    std::wstring wide(static_cast<std::size_t>(size), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), wide.data(), size);
    return wide;
}

std::string wide_to_utf8(const std::wstring& text) {
    if (text.empty()) return {};
    const int size = WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), nullptr, 0,
                                         nullptr, nullptr);
    std::string narrow(static_cast<std::size_t>(size), '\0');
    WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), narrow.data(), size, nullptr,
                        nullptr);
    return narrow;
}

class Host;

// One web page in one window, with its WebView2 controller and web view.
struct Page {
    explicit Page(HWND window_handle) : window(window_handle) {}
    ~Page() { Close(); }

    Page(const Page&) = delete;
    Page& operator=(const Page&) = delete;

    // Sends a message to the page. The page receives the JSON text as a string.
    void Post(const json& message) {
        if (!webview) return;
        const std::wstring text = utf8_to_wide(message.dump(-1, ' ', false, json::error_handler_t::replace));
        webview->PostWebMessageAsString(text.c_str());
    }

    // Keeps the page the same size as its window.
    void Resize() {
        if (!controller) return;
        RECT bounds{};
        GetClientRect(window, &bounds);
        controller->put_Bounds(bounds);
    }

    // Closes the WebView2 control. Done before the window goes, so the page is shut down cleanly.
    void Close() {
        if (controller) {
            controller->Close();
            controller->Release();
            controller = nullptr;
        }
        if (webview) {
            webview->Release();
            webview = nullptr;
        }
    }

    HWND window;
    ICoreWebView2Controller* controller = nullptr;
    ICoreWebView2* webview = nullptr;
    EventRegistrationToken token{};
};

// COM callbacks. Each holds a reference count, and deletes itself when the count reaches zero.

class EnvironmentHandler final : public ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler {
public:
    explicit EnvironmentHandler(Host& host) : host_(host) {}
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override {
        if (riid == IID_IUnknown || riid == IID_ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler) {
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
    ControllerHandler(Host& host, Page& page) : host_(host), page_(page) {}
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override {
        if (riid == IID_IUnknown || riid == IID_ICoreWebView2CreateCoreWebView2ControllerCompletedHandler) {
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
    Page& page_;
    ULONG refs_ = 1;
};

class MessageHandler final : public ICoreWebView2WebMessageReceivedEventHandler {
public:
    MessageHandler(Host& host, Page& page) : host_(host), page_(page) {}
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
    Page& page_;
    ULONG refs_ = 1;
};

// Owns the windows, the WebView2 environment, and the router. Moves messages between them.
class Host {
public:
    Host(HWND window, HINSTANCE instance, fs::path repo_root, fs::path web_root)
        : instance_(instance),
          web_root_(std::move(web_root)),
          main_(window),
          runner_(window, repo_root),
          router_(std::move(repo_root),
                  [this](const std::string& name, const json& payload) { PostEvent(name, payload); },
                  runner_) {
        // The router asks for the lesson window to open or close, which only the window's code can do.
        router_.SetWindowAction([this](const std::string& action) {
            if (action == "open") {
                OpenLessonWindow();
            } else {
                CloseLessonWindow();
            }
        });
    }

    ~Host() { Release(); }
    Host(const Host&) = delete;
    Host& operator=(const Host&) = delete;

    bool Start() {
        HMODULE loader = LoadLibraryW(L"WebView2Loader.dll");
        if (!loader) {
            Fail(L"WebView2Loader.dll wasn't found next to the program.", static_cast<HRESULT>(GetLastError()));
            return false;
        }
        auto create = reinterpret_cast<CreateEnvironmentFn>(reinterpret_cast<void*>(
            GetProcAddress(loader, "CreateCoreWebView2EnvironmentWithOptions")));
        if (!create) {
            Fail(L"The loader DLL doesn't export CreateCoreWebView2EnvironmentWithOptions.",
                 static_cast<HRESULT>(GetLastError()));
            return false;
        }
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
        return environment_->CreateCoreWebView2Controller(main_.window, new ControllerHandler(*this, main_));
    }

    // A page's controller is ready. Its web view gets the virtual host, its message handler, and its first page.
    HRESULT OnController(Page& page, HRESULT result, ICoreWebView2Controller* controller) {
        if (FAILED(result)) {
            Fail(L"The WebView2 controller couldn't be created.", result);
            return result;
        }
        page.controller = controller;
        page.controller->AddRef();

        HRESULT hr = page.controller->get_CoreWebView2(&page.webview);
        if (FAILED(hr)) {
            Fail(L"The WebView2 control couldn't be reached from the controller.", hr);
            return hr;
        }

        // The virtual host maps https://runner.local/ to the web folder, so the page's modules load as normal files.
        ICoreWebView2_3* webview3 = nullptr;
        hr = page.webview->QueryInterface(IID_ICoreWebView2_3, reinterpret_cast<void**>(&webview3));
        if (FAILED(hr)) {
            Fail(L"This WebView2 Runtime is too old for the lesson runner. Install the current Evergreen Runtime.", hr);
            return hr;
        }
        hr = webview3->SetVirtualHostNameToFolderMapping(kVirtualHost, web_root_.c_str(),
                                                         COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND_ALLOW);
        webview3->Release();
        if (FAILED(hr)) {
            Fail(L"The lesson runner's web folder couldn't be mapped.", hr);
            return hr;
        }

        page.Resize();

        hr = page.webview->add_WebMessageReceived(new MessageHandler(*this, page), &page.token);
        if (FAILED(hr)) {
            Fail(L"Couldn't listen for messages from the page.", hr);
            return hr;
        }
        return page.webview->Navigate(&page == &main_ ? kStartPage : kLessonPage);
    }

    // A message from a page: { kind: "command", id, command, args }. The reply goes back to that page.
    HRESULT OnMessage(Page& page, ICoreWebView2WebMessageReceivedEventArgs* args) {
        LPWSTR raw = nullptr;
        HRESULT hr = args->TryGetWebMessageAsString(&raw);
        if (FAILED(hr) || !raw) return hr;
        const std::string text = wide_to_utf8(raw);
        CoTaskMemFree(raw);

        json message;
        try {
            message = json::parse(text);
        } catch (const json::exception&) {
            return S_OK;  // Not JSON, so it isn't a command from the bridge.
        }
        if (message.value("kind", "") != "command") return S_OK;

        json reply{{"kind", "reply"}, {"id", message.value("id", 0)}};
        try {
            const json args_value = message.value("args", json::object());
            reply["result"] = router_.handle(message.value("command", ""), args_value);
        } catch (const std::exception& error) {
            reply["error"] = error.what();
        }
        page.Post(reply);
        return S_OK;
    }

    // Opens the pop-out lesson window, or brings the open one to the front.
    void OpenLessonWindow() {
        if (lesson_window_) {
            ShowWindow(lesson_window_, SW_RESTORE);
            SetForegroundWindow(lesson_window_);
            return;
        }
        lesson_window_ = CreateWindowExW(0, kLessonWindowClass, L"Lesson", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                                         CW_USEDEFAULT, 900, 720, nullptr, nullptr, instance_, this);
        if (!lesson_window_) {
            Fail(L"The lesson window couldn't be created.", static_cast<HRESULT>(GetLastError()));
            return;
        }
        lesson_ = std::make_unique<Page>(lesson_window_);
        environment_->CreateCoreWebView2Controller(lesson_window_, new ControllerHandler(*this, *lesson_));
        ShowWindow(lesson_window_, SW_SHOW);
        PostEvent("lesson-popped", nullptr);
    }

    // Closes the pop-out lesson window. The lesson returns to the main window.
    void CloseLessonWindow() {
        if (lesson_window_) DestroyWindow(lesson_window_);
    }

    // The lesson window has gone, however it closed. Its page is released, and the main window is told.
    void OnLessonWindowDestroyed() {
        lesson_.reset();
        lesson_window_ = nullptr;
        PostEvent("lesson-docked", nullptr);
    }

    bool IsLessonWindow(HWND window) const { return lesson_window_ && window == lesson_window_; }
    HWND LessonWindow() const { return lesson_window_; }

    // Keeps whichever page's window was resized the right size.
    void OnWindowResized(HWND window) {
        if (window == main_.window) {
            main_.Resize();
        } else if (lesson_ && window == lesson_->window) {
            lesson_->Resize();
        }
    }

    // Sends the output and results that the runner has queued. Called on the window's thread.
    void FlushRunnerEvents() {
        for (auto& [name, payload] : runner_.TakeEvents()) {
            PostEvent(name, payload);
        }
    }

private:
    // Events go to every open page, since each one may show the lesson or the run's output.
    void PostEvent(const std::string& name, const json& payload) {
        const json message{{"kind", "event"}, {"event", name}, {"payload", payload}};
        main_.Post(message);
        if (lesson_) lesson_->Post(message);
    }

    void Release() {
        lesson_.reset();
        main_.Close();
        if (environment_) {
            environment_->Release();
            environment_ = nullptr;
        }
    }

    HINSTANCE instance_;
    fs::path web_root_;
    Page main_;
    lesson::Runner runner_;
    lesson::Router router_;
    ICoreWebView2Environment* environment_ = nullptr;
    HWND lesson_window_ = nullptr;
    std::unique_ptr<Page> lesson_;
};

HRESULT STDMETHODCALLTYPE EnvironmentHandler::Invoke(HRESULT result, ICoreWebView2Environment* environment) {
    return host_.OnEnvironment(result, environment);
}

HRESULT STDMETHODCALLTYPE ControllerHandler::Invoke(HRESULT result, ICoreWebView2Controller* controller) {
    return host_.OnController(page_, result, controller);
}

HRESULT STDMETHODCALLTYPE MessageHandler::Invoke(ICoreWebView2* sender,
                                                 ICoreWebView2WebMessageReceivedEventArgs* args) {
    (void)sender;
    return host_.OnMessage(page_, args);
}

Host* g_host = nullptr;

// Both windows share this procedure. The lesson window keeps its Host in GWLP_USERDATA. The main window uses g_host.
LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    if (message == WM_NCCREATE) {
        const auto* create = reinterpret_cast<const CREATESTRUCTW*>(lparam);
        SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(create->lpCreateParams));
    }
    Host* host = reinterpret_cast<Host*>(GetWindowLongPtrW(window, GWLP_USERDATA));
    if (!host) host = g_host;

    switch (message) {
        case WM_SIZE:
            if (host) host->OnWindowResized(window);
            return 0;
        case lesson::kRunnerEventsMessage:
            if (g_host) g_host->FlushRunnerEvents();
            return 0;
        case WM_DESTROY:
            if (host && host->IsLessonWindow(window)) {
                host->OnLessonWindowDestroyed();
                return 0;
            }
            // Closing the main window closes the lesson window too, so the program can exit.
            if (g_host && g_host->LessonWindow()) DestroyWindow(g_host->LessonWindow());
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcW(window, message, wparam, lparam);
    }
}

}  // namespace

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE /*previous*/, PWSTR /*command_line*/, int show) {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        Fail(L"COM couldn't start.", hr);
        return 1;
    }

    // The repository root is found from the program's folder, so the runner works wherever the repo is.
    wchar_t module_path[MAX_PATH];
    GetModuleFileNameW(nullptr, module_path, MAX_PATH);
    const fs::path repo_root = lesson::find_repo_root(fs::path(module_path).parent_path());
    const fs::path web_root = repo_root / "lesson-runner" / "web";
    if (!fs::is_regular_file(web_root / "index.html")) {
        Fail(L"The lesson runner's web folder wasn't found. Check the repository layout.", 0);
        CoUninitialize();
        return 1;
    }

    // The icon is resource 1, embedded from app.ico. Windows uses it for the title bar and the taskbar.
    WNDCLASSW window_class{};
    window_class.lpfnWndProc = WndProc;
    window_class.hInstance = instance;
    window_class.lpszClassName = kWindowClass;
    window_class.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    window_class.hIcon = LoadIconW(instance, MAKEINTRESOURCEW(1));
    RegisterClassW(&window_class);

    WNDCLASSW lesson_class{};
    lesson_class.lpfnWndProc = WndProc;
    lesson_class.hInstance = instance;
    lesson_class.lpszClassName = kLessonWindowClass;
    lesson_class.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    lesson_class.hIcon = LoadIconW(instance, MAKEINTRESOURCEW(1));
    RegisterClassW(&lesson_class);

    HWND window = CreateWindowExW(0, kWindowClass, L"Lesson Runner", WS_OVERLAPPEDWINDOW,
                                  CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800,
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
        Host host(window, instance, repo_root, web_root);
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
