#pragma once

#include "Console.hpp"
#include "String.hpp"
#include <fstream>
#include <optional>

namespace SSBL {
enum class LogLevel {
    NON = 0b0000,
    INF = 0b0001,
    WRN = 0b0010,
    ERR = 0b0100,
    FTL = 0b1000,
    ALL = 0b1111
};

String LogLevelToString(LogLevel level);
Color LogLevelToColor(LogLevel level);

struct LoggerSettings {
    bool useColor = false;
    bool showTimestamp = true;
    String timeFormat = "%Y-%m-%d %D %H:%M:%S";
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

class LogOutputStream final : public std::streambuf {
public:
    explicit LogOutputStream(Logger &logger);

protected:
    int overflow(int character) override;
    std::streamsize xsputn(const char *string, std::streamsize size) override;

private:
    Logger &m_logger;
};

class ErrorOutputStream final : public std::streambuf {
public:
    explicit ErrorOutputStream(Logger &logger);

protected:
    int overflow(int character) override;
    std::streamsize xsputn(const char *string, std::streamsize size) override;

private:
    Logger &m_logger;
};

class Logger {
public:
    explicit Logger(
        LoggerSettings settings = LoggerSettings(), const String &outputFile = String::Empty());
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
    Logger &EnableRotatingFiles(const String &format, size_t sizeLimitBytes);
    Logger &DisableRotatingFiles();

    void operator<<(const String &string);
    void Flush();

private:
    void UpdateRotatingFiles();
    void ProcessStream();

    static std::optional<std::streambuf *> cout;
    static std::optional<std::streambuf *> cerr;

    LogOutputStream m_outputStream;
    ErrorOutputStream m_errorStream;

    LoggerSettings m_settings;
    String m_stream;
    LogLevel m_currentLevel = LogLevel::INF;
    size_t m_insertCount = 0;

    std::ofstream m_file;
    String m_filename;

    std::ofstream m_rotatingFile;
    bool m_rotatingFiles = false;
    size_t m_rotatingFileSize = 0;
    String m_rotatingFileFormat;
    size_t m_rotatingFileIndex = 0;
};
} // namespace SSBL