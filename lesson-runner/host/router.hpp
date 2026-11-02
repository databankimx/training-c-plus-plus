// router.hpp: answers the commands the front end sends, and sends events back to it.
//
// The page sends { "kind": "command", "id": 7, "command": "read_lesson", "args": { ... } }. The router handles it
// and returns the result as JSON. Errors are thrown as std::runtime_error, and the message is what the page shows.

#pragma once

#include <json.hpp>
#include "runner.hpp"

#include <filesystem>
#include <functional>
#include <string>

namespace lesson {

// Sends an event to the page: its name, and its payload.
using EventSink = std::function<void(const std::string& name, const nlohmann::json& payload)>;

class Router {
public:
    Router(std::filesystem::path repo_root, EventSink events, Runner& runner);

    // Lets the window decide what opening and closing the lesson window does. Called with "open" or "dock".
    void SetWindowAction(std::function<void(const std::string& action)> action);

    // Runs one command. Returns the result, or throws std::runtime_error with the text the page should show.
    nlohmann::json handle(const std::string& command, const nlohmann::json& args);

private:
    std::filesystem::path root_;
    EventSink events_;
    Runner& runner_;
    std::function<void(const std::string& action)> window_action_;
    std::string lesson_title_;
    std::string lesson_text_;
    bool light_ = false;
};

}  // namespace lesson
