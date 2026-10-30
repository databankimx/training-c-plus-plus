// runner.cpp: see runner.hpp.

#include "runner.hpp"
#include "discovery.hpp"

#include <cctype>
#include <cstddef>
#include <fstream>
#include <map>
#include <stdexcept>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace lesson {
namespace {

// Where cmake, ninja, and g++ are installed, from MSYS2's UCRT64 environment.
constexpr const wchar_t* kToolchainBin = L"C:\\msys64\\ucrt64\\bin";

std::wstring utf8_to_wide(const std::string& text) {
    if (text.empty()) return {};
    const int size = MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), nullptr, 0);
    std::wstring wide(static_cast<std::size_t>(size), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), wide.data(), size);
    return wide;
}

// NAME=value, where NAME is a plain identifier, such as IGNORE_CASE=1.
bool is_assignment(const std::string& arg) {
    const auto equals = arg.find('=');
    if (equals == std::string::npos || equals == 0) return false;
    if (std::isdigit(static_cast<unsigned char>(arg[0]))) return false;
    for (std::size_t i = 0; i < equals; ++i) {
        const unsigned char c = static_cast<unsigned char>(arg[i]);
        if (!(std::isalnum(c) || c == '_')) return false;
    }
    return true;
}

std::wstring quoted(const fs::path& path) {
    return L"\"" + path.wstring() + L"\"";
}

// Every regular file under a run's folder, with its last write time. The build folder is skipped, since it holds
// compiler output rather than anything the program wrote.
using FileTimes = std::map<fs::path, fs::file_time_type>;

FileTimes SnapshotFiles(const fs::path& folder) {
    FileTimes files;
    for (auto it = fs::recursive_directory_iterator(folder); it != fs::recursive_directory_iterator(); ++it) {
        if (it.depth() == 0 && it->is_directory() && it->path().filename() == "build") {
            it.disable_recursion_pending();
            continue;
        }
        if (it->is_regular_file()) {
            files[it->path()] = it->last_write_time();
        }
    }
    return files;
}

// The files a run created or changed, as a JSON array of { name, path } objects.
json ChangedFiles(const FileTimes& before, const fs::path& folder) {
    json changed = json::array();
    for (const auto& [path, time] : SnapshotFiles(folder)) {
        const auto old = before.find(path);
        if (old == before.end() || old->second != time) {
            changed.push_back(json{{"name", path.filename().string()}, {"path", path.string()}});
        }
    }
    return changed;
}

void CloseIfSet(HANDLE& handle) {
    if (handle) {
        CloseHandle(handle);
        handle = nullptr;
    }
}

}  // namespace

Runner::Runner(HWND window, fs::path repo_root) : window_(window), repo_root_(std::move(repo_root)) {
    // The build tools are found on PATH by every child process, so the toolchain folder goes first.
    const DWORD size = GetEnvironmentVariableW(L"PATH", nullptr, 0);
    std::wstring current;
    if (size > 0) {
        current.resize(size);
        GetEnvironmentVariableW(L"PATH", current.data(), size);
        current.resize(size - 1);
    }
    SetEnvironmentVariableW(L"PATH", (std::wstring(kToolchainBin) + L";" + current).c_str());
}

Runner::~Runner() {
    Stop();
    if (worker_.joinable()) worker_.join();
}

void Runner::Start(const RunRequest& request) {
    if (running_) throw std::runtime_error("A program is already running. Stop it first.");
    // The previous run has finished, so its thread can be joined before a new one starts.
    if (worker_.joinable()) worker_.join();

    // Leading NAME=value items set environment variables for this run only.
    RunRequest copy = request;
    std::vector<std::pair<std::string, std::string>> environment;
    std::size_t split = 0;
    while (split < copy.args.size() && is_assignment(copy.args[split])) {
        const std::string& arg = copy.args[split];
        const auto equals = arg.find('=');
        environment.emplace_back(arg.substr(0, equals), arg.substr(equals + 1));
        ++split;
    }
    copy.args.erase(copy.args.begin(), copy.args.begin() + static_cast<std::ptrdiff_t>(split));

    cancelled_ = false;
    running_ = true;
    worker_ = std::thread([this, copy = std::move(copy), environment = std::move(environment)]() mutable {
        Work(std::move(copy), std::move(environment));
    });
}

void Runner::Stop() {
    cancelled_ = true;
    std::lock_guard lock(mutex_);
    if (current_job_) TerminateJobObject(current_job_, 1);
}

void Runner::SendInput(const std::string& text) {
    std::lock_guard lock(mutex_);
    if (!input_) throw std::runtime_error("No program is running.");
    DWORD written = 0;
    if (!WriteFile(input_, text.data(), static_cast<DWORD>(text.size()), &written, nullptr)) {
        throw std::runtime_error("The program has stopped reading input.");
    }
}

std::vector<std::pair<std::string, json>> Runner::TakeEvents() {
    std::lock_guard lock(mutex_);
    return std::exchange(events_, {});
}

void Runner::Emit(const std::string& name, const json& payload) {
    {
        std::lock_guard lock(mutex_);
        events_.emplace_back(name, payload);
    }
    // The window's thread sends queued events to the page, so the page is only ever touched there.
    PostMessageW(window_, kRunnerEventsMessage, 0, 0);
}

void Runner::Finish(std::optional<unsigned long> code) {
    json payload{{"code", code ? json(static_cast<int>(*code)) : json(nullptr)}};
    running_ = false;
    Emit("run-finished", payload);
}

// Copies the step to the run's work folder, without its build folder, and writes the edited main.cpp into it.
fs::path Runner::PrepareWorkCopy(const RunRequest& request) {
    const fs::path work = work_root(repo_root_) / request.step.filename();
    fs::create_directories(work);
    for (const auto& entry : fs::directory_iterator(request.step)) {
        if (entry.path().filename() == "build") continue;
        fs::copy(entry.path(), work / entry.path().filename(),
                 fs::copy_options::recursive | fs::copy_options::overwrite_existing);
    }
    if (request.source) {
        fs::create_directories(work / "src");
        std::ofstream out(work / "src" / "main.cpp", std::ios::binary);
        if (!out) throw std::runtime_error("Could not save the edited code.");
        out << *request.source;
    }
    return work;
}

// The run itself, on the worker thread: configure, build, then run the program or its tests.
void Runner::Work(RunRequest request, std::vector<std::pair<std::string, std::string>> environment) {
    const std::string name = request.step.filename().string();
    auto status = [this](const std::string& line) {
        Emit("run-output", json{{"stream", "stdout"}, {"text", line + "\n"}});
    };

    fs::path folder;
    try {
        folder = PrepareWorkCopy(request);
    } catch (const std::exception& error) {
        Emit("run-output", json{{"stream", "stderr"}, {"text", std::string(error.what()) + "\n"}});
        Finish(1UL);
        return;
    }
    const fs::path build = folder / "build";

    // Stops the run if the user asked for it, or if a phase failed. Returns true when the run is over.
    auto phase_failed = [&](std::optional<unsigned long> code) {
        if (cancelled_) {
            Finish(std::nullopt);
            return true;
        }
        if (!code || *code != 0) {
            Finish(code.value_or(1UL));
            return true;
        }
        return false;
    };

    status("Configuring " + name + "...");
    const std::wstring configure = L"cmake -S " + quoted(folder) + L" -B " + quoted(build) +
                                   L" -G Ninja -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug -DLESSON_BACKTRACE=" +
                                   (request.backtrace ? L"ON" : L"OFF");
    // Every option the step declares is passed on every configure, ON or OFF, so a value from an earlier run can't
    // linger in the build's cache.
    std::wstring configureWithOptions = configure;
    for (const auto& [option, on] : request.options) {
        configureWithOptions += L" -D" + utf8_to_wide(option) + (on ? L"=ON" : L"=OFF");
    }
    if (phase_failed(RunChild(configureWithOptions, folder, false, "CMake"))) return;

    status("Building " + name + "...");
    if (phase_failed(RunChild(L"cmake --build " + quoted(build), folder, false, "CMake"))) return;

    if (request.test) {
        status("Testing " + name + "...");
        const auto code = RunChild(L"ctest --test-dir " + quoted(build) + L" --output-on-failure", folder, false, "CTest");
        if (cancelled_) {
            Finish(std::nullopt);
        } else {
            Finish(code.value_or(1UL));
        }
        return;
    }

    const fs::path program = build / "program.exe";
    if (!fs::is_regular_file(program)) {
        Emit("run-output", json{{"stream", "stderr"},
                                {"text", "This step didn't build a program. Its CMakeLists.txt should build an "
                                         "executable named program.\n"}});
        Finish(1UL);
        return;
    }

    std::wstring command = quoted(program);
    for (const std::string& arg : request.args) {
        command += L" \"" + utf8_to_wide(arg) + L"\"";
    }
    for (const auto& [variable, value] : environment) {
        SetEnvironmentVariableW(utf8_to_wide(variable).c_str(), utf8_to_wide(value).c_str());
    }
    const FileTimes before = SnapshotFiles(folder);
    status("Running program.exe");
    // A blank line sets the program's output off from the build lines above it.
    Emit("run-output", json{{"stream", "stdout"}, {"text", "\n"}});
    const auto code = RunChild(command, folder, true, "program.exe");
    for (const auto& [variable, value] : environment) {
        SetEnvironmentVariableW(utf8_to_wide(variable).c_str(), nullptr);
    }

    // Files the program created or changed are offered to the page, to open in their default application.
    Emit("output-files", ChangedFiles(before, folder));

    if (cancelled_) {
        Finish(std::nullopt);
    } else {
        Finish(code.value_or(1UL));
    }
}

// Runs one process with its output on pipes, and waits for it. Returns its exit code, or nothing if it couldn't start.
// When interactive, its standard input is a pipe that SendInput writes to. Otherwise the input is empty.
std::optional<unsigned long> Runner::RunChild(const std::wstring& command_line, const fs::path& folder,
                                              bool interactive, const std::string& what) {
    SECURITY_ATTRIBUTES inherit{sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE};
    HANDLE out_read = nullptr, out_write = nullptr, err_read = nullptr, err_write = nullptr;
    HANDLE in_read = nullptr, in_write = nullptr;

    auto fail = [&](const char* what) -> std::optional<unsigned long> {
        Emit("run-output", json{{"stream", "stderr"},
                                {"text", std::string(what) + " (error " + std::to_string(GetLastError()) + ")\n"}});
        CloseIfSet(out_read);
        CloseIfSet(out_write);
        CloseIfSet(err_read);
        CloseIfSet(err_write);
        CloseIfSet(in_read);
        CloseIfSet(in_write);
        return std::nullopt;
    };

    // The parent keeps the read ends of the output pipes, and the write end of the input pipe. The children get the rest.
    if (!CreatePipe(&out_read, &out_write, &inherit, 0)) return fail("Could not create the output pipe.");
    SetHandleInformation(out_read, HANDLE_FLAG_INHERIT, 0);
    if (!CreatePipe(&err_read, &err_write, &inherit, 0)) return fail("Could not create the error pipe.");
    SetHandleInformation(err_read, HANDLE_FLAG_INHERIT, 0);
    if (interactive) {
        if (!CreatePipe(&in_read, &in_write, &inherit, 0)) return fail("Could not create the input pipe.");
        SetHandleInformation(in_write, HANDLE_FLAG_INHERIT, 0);
    } else {
        in_read = CreateFileW(L"NUL", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, &inherit, OPEN_EXISTING, 0,
                              nullptr);
        if (in_read == INVALID_HANDLE_VALUE) {
            in_read = nullptr;
            return fail("Could not open the input.");
        }
    }

    // A Job Object holds the process and anything it starts. Stop ends the job, which ends the whole tree.
    HANDLE job = CreateJobObjectW(nullptr, nullptr);
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits{};
    limits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
    SetInformationJobObject(job, JobObjectExtendedLimitInformation, &limits, sizeof limits);

    STARTUPINFOW startup{};
    startup.cb = sizeof startup;
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = in_read;
    startup.hStdOutput = out_write;
    startup.hStdError = err_write;

    PROCESS_INFORMATION process{};
    std::wstring line = command_line;  // CreateProcess may change its buffer, so it gets a copy.
    const BOOL started = CreateProcessW(nullptr, line.data(), nullptr, nullptr, TRUE,
                                        CREATE_SUSPENDED | CREATE_NO_WINDOW, nullptr, folder.c_str(), &startup,
                                        &process);
    if (!started) {
        CloseHandle(job);
        // Only the step's own program is run interactively, so the other runs are build tools. The advice differs:
        // a program that was built but won't start is usually blocked by security software, and a build tool that won't
        // start points at the toolchain.
        if (interactive) {
            return fail(("Windows would not start " + what + ". It was built, but security software may have blocked or "
                         "removed it. See the troubleshooting section of QUICKSTART").c_str());
        }
        return fail(("Could not start " + what + ". Is the toolchain installed in C:\\msys64\\ucrt64?").c_str());
    }

    // The children have their own copies now, so the parent closes its copies of their ends.
    CloseIfSet(out_write);
    CloseIfSet(err_write);
    CloseIfSet(in_read);

    AssignProcessToJobObject(job, process.hProcess);
    ResumeThread(process.hThread);
    CloseHandle(process.hThread);

    {
        std::lock_guard lock(mutex_);
        current_job_ = job;
        input_ = interactive ? in_write : nullptr;
    }
    // Stop may have been asked for before the job was recorded, so it is checked again here.
    if (cancelled_) TerminateJobObject(job, 1);

    auto pump = [this](HANDLE pipe, const char* stream) {
        char buffer[4096];
        DWORD read = 0;
        while (ReadFile(pipe, buffer, sizeof buffer, &read, nullptr) && read > 0) {
            Emit("run-output", json{{"stream", stream}, {"text", std::string(buffer, read)}});
        }
    };
    std::thread out_thread(pump, out_read, "stdout");
    std::thread err_thread(pump, err_read, "stderr");

    WaitForSingleObject(process.hProcess, INFINITE);
    DWORD exit_code = 0;
    GetExitCodeProcess(process.hProcess, &exit_code);
    CloseHandle(process.hProcess);

    out_thread.join();
    err_thread.join();

    {
        std::lock_guard lock(mutex_);
        current_job_ = nullptr;
        input_ = nullptr;
    }
    CloseIfSet(in_write);
    CloseIfSet(out_read);
    CloseIfSet(err_read);
    CloseHandle(job);

    return static_cast<unsigned long>(exit_code);
}

}  // namespace lesson
