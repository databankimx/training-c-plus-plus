// runner.hpp: builds and runs a lesson step, and streams its output to the page.
//
// A run copies the step into a temporary folder (so the repository is never changed), writes the edited main.cpp
// if there is one, then configures and builds it with CMake and Ninja. Then it runs the step's program, or its tests.
// Output arrives on pipes, on threads, and is queued as events. The window's thread sends them to the page.

#pragma once

#include <json.hpp>

#include <windows.h>

#include <atomic>
#include <filesystem>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace lesson {

// Posted to the window when events are waiting. The window's thread then calls Runner::TakeEvents.
constexpr UINT kRunnerEventsMessage = WM_APP + 1;

struct RunRequest {
    std::filesystem::path step;
    std::optional<std::string> source;  // The edited main.cpp, when the reader has changed it.
    bool backtrace = false;             // Builds with stack-trace support.
    bool test = false;                  // Runs the step's tests instead of its program.
    std::vector<std::string> args;      // Leading NAME=value items become environment variables for the run.
};

class Runner {
public:
    Runner(HWND window, std::filesystem::path repo_root);
    ~Runner();

    Runner(const Runner&) = delete;
    Runner& operator=(const Runner&) = delete;

    // Starts a run in the background. Throws std::runtime_error if one is already running.
    void Start(const RunRequest& request);

    // Stops the current run, and everything it started.
    void Stop();

    // Sends a line to the running program's standard input. Throws if no program is waiting for input.
    void SendInput(const std::string& text);

    // The events queued since the last call, as (name, payload) pairs. Call from the window's thread.
    std::vector<std::pair<std::string, nlohmann::json>> TakeEvents();

private:
    struct Child;

    void Work(RunRequest request, std::vector<std::pair<std::string, std::string>> environment);
    std::optional<unsigned long> RunChild(const std::wstring& command_line, const std::filesystem::path& folder,
                                          bool interactive);
    std::filesystem::path PrepareWorkCopy(const RunRequest& request);
    void Emit(const std::string& name, const nlohmann::json& payload);
    void Finish(std::optional<unsigned long> code);

    HWND window_;
    std::filesystem::path repo_root_;

    std::mutex mutex_;
    std::vector<std::pair<std::string, nlohmann::json>> events_;
    HANDLE current_job_ = nullptr;   // The Job Object of the process that is running now.
    HANDLE input_ = nullptr;         // Write end of the running program's standard input.
    std::atomic<bool> running_{false};
    std::atomic<bool> cancelled_{false};
    std::thread worker_;
};

}  // namespace lesson
