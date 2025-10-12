export module core.logging;

export class ILogger
{
    enum LogLevel
    {
        Debug,
        Info,
        Warning,
        Error
    };

    virtual ~ILogger() = default;
    virtual void log(LogLevel level, const char *message) = 0;
};
