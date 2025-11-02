#include <print>
#include "logger.h"

void Logger::log(LogLevel level, std::string_view message) {

    constexpr auto reset = "\033[0m";
    std::print("{}[{}] {}{}\n", levelColor(level), levelToString(level), message, reset);
}

std::string_view Logger::levelToString(const LogLevel level) {
    switch (level) {
        case LogLevel::Trace:
            return "TRACE";
        case LogLevel::Debug:
            return "DEBUG";
        case LogLevel::Info:
            return "INFO";
        case LogLevel::Warning:
            return "WARN";
        case LogLevel::Error:
            return "ERROR";
        case LogLevel::Fatal:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}

std::string_view Logger::levelColor(const LogLevel level) {
    switch (level) {
        case LogLevel::Trace:
            return "\033[90m"; // gray
        case LogLevel::Debug:
            return "\033[36m"; // cyan
        case LogLevel::Info:
            return "\033[32m";  // green
        case LogLevel::Warning:
            return "\033[33m"; // yellow
        case LogLevel::Error:
            return "\033[31m"; // red
        case LogLevel::Fatal:
            return "\033[41m"; // red background
        default:
            return "\033[0m";
    }
}
