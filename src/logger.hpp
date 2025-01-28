#pragma once

#include <sstream>

namespace Logger {
    enum class LogLevel {
        None    = 0,
        Fatal   = 1,
        Error   = 2,
        Warning = 4,
        Info    = 8,
        All     = Fatal | Error | Warning | Info
    };

    constexpr LogLevel operator|(LogLevel a, LogLevel b) {
        return static_cast<LogLevel>(
            static_cast<char>(a) | static_cast<char>(b)
        );
    }

    constexpr LogLevel operator&(LogLevel a, LogLevel b) {
        return static_cast<LogLevel>(
            static_cast<char>(a) & static_cast<char>(b)
        );
    }

    constexpr LogLevel operator~(LogLevel level) {
        return static_cast<LogLevel>(~static_cast<char>(level));
    }

    inline LogLevel logLevel = LogLevel::All;
    inline bool showTimestamp = true;
    inline bool useColor = false;

    std::string logLevelToString(LogLevel level);
    std::string getTimestamp();

#if _WIN32
    int getColor(LogLevel level);
    void setWindowsColor(int color);
#else
    std::string getColor(LogLevel level);
#endif

    class LoggerStream {
    public:
        explicit LoggerStream(LogLevel level);
        ~LoggerStream();

        template <typename T>
        LoggerStream &operator<<(T &message) {
            strStream << message;
            return *this;
        }

    private:
        std::ostringstream strStream;
        LogLevel messageLogLevel;
    };

    LoggerStream log(LogLevel level);
} // namespace Logger

using Logger::LogLevel;