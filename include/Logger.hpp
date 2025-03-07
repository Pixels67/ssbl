#pragma once

#include "Console.hpp"
#include "String.hpp"
#include <fstream>
#include <optional>
#include <sstream>

namespace SSBL {
enum class LogLevel {
    NON = 0b0000,
    INF = 0b0001,
    WRN = 0b0010,
    ERR = 0b0100,
    FTL = 0b1000,
    ALL = 0b1111,
};

String LogLevelToString(LogLevel level);
Color LogLevelToColor(LogLevel level);

struct LoggerSettings {
    bool useColor          = false;
    bool showTimestamp     = true;
    String timeFormat = "%y-%m-%d %D %H:%M:%S";
};

class Logger;

class LoggerStream {
public:
    explicit LoggerStream(Logger &logger);
    ~LoggerStream();

    LoggerStream &operator<<(const String &string);

private:
    Logger &m_logger;
};

class Logger {
public:
    explicit Logger(const LoggerSettings &settings = LoggerSettings(), const String &outputFile = String::Empty());
    explicit Logger(const String &outputFile);
    ~Logger();

    LoggerStream Log(LogLevel level = LogLevel::INF);

    LoggerStream LogWarn();
    LoggerStream LogError();
    LoggerStream LogFatal();

    Logger &UseColor(bool useColor);
    Logger &ShowTimestamp(bool showTimestamp);
    Logger &SetOutputFile(const String &fileName);
    Logger &SetTimeFormat(const String &timeFormat);

    void operator<<(const String &string);
    void Flush();

private:
    void ProcessStream();

    LoggerSettings m_settings;
    String m_stream;
    LogLevel m_currentLevel = LogLevel::INF;
    size_t m_insertCount = 0;
    std::ofstream m_file;
};
} // namespace SSBL