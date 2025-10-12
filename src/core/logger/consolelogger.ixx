module;

#include <iostream>

export module core.logger.console;

import core.logger;

export class ConsoleLogger final : public ILogger {
public:
    void log(const LogLevel level, const std::string_view message) override {
        std::string prefix;

        switch (level) {
            // case LogLevel::Trace: prefix = "[TRACE] "; break;
            case LogLevel::Debug:
                prefix = "[DEBUG] ";
                break;
            case LogLevel::Info:
                prefix = "[INFO]  ";
                break;
            case LogLevel::Warning:
                prefix = "[WARNING]  ";
                break;
            case LogLevel::Error:
                prefix = "[ERROR] ";
                break;
            // case LogLevel::Fatal: prefix = "[FATAL] "; break;
        }

        std::cout << colorFor(level) << prefix << message << "\033[0m\n";
    };

    ~ConsoleLogger() override = default;
private:
    static const char* colorFor(const LogLevel level) {
        switch (level) {
            case LogLevel::Info: return "\033[32m";    // зелёный
            case LogLevel::Warning: return "\033[33m"; // жёлтый
            case LogLevel::Error: return "\033[31m";   // красный
            case LogLevel::Debug: return "\033[36m";   // циан
            default: return "\033[0m";
        }
    }
};
