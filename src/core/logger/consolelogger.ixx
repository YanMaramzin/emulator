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

        std::cout << prefix << message << std::endl;
    };

    ~ConsoleLogger() override;
};