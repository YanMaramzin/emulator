module;

#include <string_view>

export module core.logger;

export enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

export class ILogger
{
    virtual ~ILogger() = default;
    virtual void log(LogLevel level, const std::string_view message) = 0;
};
