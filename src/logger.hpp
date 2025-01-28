#pragma once

#include <sstream>

namespace Logger {
    enum class LogLevel {
        NONE    = 0,
        FATAL   = 1,
        ERROR   = 2,
        WARNING = 4,
        INFO    = 8,
        ALL     = FATAL | ERROR | WARNING | INFO
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

    inline LogLevel logLevel = LogLevel::ALL;
    inline bool showTimestamp = true;

    std::string logLevelToString(LogLevel level);
    std::string getTimestamp();

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