// router.cpp: see router.hpp.

#include "router.hpp"

#include "commands.hpp"
#include "discovery.hpp"

#include <stdexcept>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace lesson {
namespace {

// Reads a required string argument, such as the path of a step.
std::string string_arg(const json& args, const char* name) {
    if (!args.contains(name) || !args.at(name).is_string()) {
        throw std::runtime_error(std::string("Missing argument: ") + name);
    }
    return args.at(name).get<std::string>();
}

}  // namespace

Router::Router(fs::path repo_root, EventSink events, Runner& runner)
    : root_(std::move(repo_root)), events_(std::move(events)), runner_(runner) {}

void Router::SetWindowAction(std::function<void(const std::string& action)> action) {
    window_action_ = std::move(action);
}

json Router::handle(const std::string& command, const json& args) {
    // Lesson and step reading.
    if (command == "list_parts") {
        return list_parts(root_);
    }
    if (command == "list_chapters") {
        return json(discover(root_));
    }
    if (command == "read_lesson") {
        return read_lesson(string_arg(args, "path"));
    }
    if (command == "read_step_file") {
        return read_step_file(string_arg(args, "path"), string_arg(args, "file"));
    }
    if (command == "read_commands") {
        return read_commands(string_arg(args, "path"));
    }
    if (command == "list_source_files") {
        return list_source_files(string_arg(args, "path"));
    }
    if (command == "read_source") {
        return read_source(string_arg(args, "path"), string_arg(args, "file"));
    }

    // The lesson on screen, which the pop-out window reads.
    if (command == "set_lesson") {
        lesson_title_ = string_arg(args, "title");
        lesson_text_ = string_arg(args, "text");
        events_("lesson-updated", json{{"title", lesson_title_}, {"text", lesson_text_}});
        return nullptr;
    }
    if (command == "get_lesson") {
        return json{{"title", lesson_title_}, {"text", lesson_text_}};
    }

    // Theme, shared by every window.
    if (command == "set_theme") {
        light_ = args.value("light", false);
        events_("theme-changed", light_);
        return nullptr;
    }
    if (command == "get_theme") {
        return light_;
    }

    // Links: #goto/ jumps are sent to the page, and web and mail links open in the browser.
    if (command == "navigate_to") {
        events_("goto", string_arg(args, "name"));
        return nullptr;
    }
    if (command == "open_visualizer") {
        // The visualizer is copied into the run's work folder on each run, so it is opened from there, beside the trace.
        const fs::path page = work_root(root_) / fs::path(string_arg(args, "path")).filename() / "visualize.html";
        if (!fs::is_regular_file(page)) {
            throw std::runtime_error("Run this step once, so its trace is written, then press Visualize.");
        }
        open_file(page.string(), work_root(root_));
        return nullptr;
    }
    if (command == "open_file") {
        open_file(string_arg(args, "path"), work_root(root_));
        return nullptr;
    }
    if (command == "open_external") {
        open_external(string_arg(args, "url"));
        return nullptr;
    }

    // Not built yet. The page shows these messages as they are.
    if (command == "open_lesson_window") {
        if (window_action_) window_action_("open");
        return nullptr;
    }
    if (command == "dock_lesson") {
        if (window_action_) window_action_("dock");
        return nullptr;
    }
    if (command == "run_step") {
        RunRequest request;
        request.step = string_arg(args, "path");
        if (args.contains("source") && args.at("source").is_string()) {
            request.source = args.at("source").get<std::string>();
        }
        request.backtrace = args.value("backtrace", false);
        request.test = args.value("test", false);
        for (const json& arg : args.value("args", json::array())) {
            request.args.push_back(arg.get<std::string>());
        }
        runner_.Start(request);
        return nullptr;
    }
    if (command == "send_input") {
        runner_.SendInput(string_arg(args, "text"));
        return nullptr;
    }
    if (command == "stop_run") {
        runner_.Stop();
        return nullptr;
    }

    throw std::runtime_error("Unknown command: " + command);
}

}  // namespace lesson
