#pragma once
#include <string_view>

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

class Logger {
public:
    static void log(LogLevel level, std::string_view message);
private:
    static std::string_view levelToString(LogLevel level);
    static std::string_view levelColor(LogLevel level);
};


