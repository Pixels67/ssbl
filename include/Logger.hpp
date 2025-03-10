#pragma once

#include "Console.hpp"
#include "String.hpp"
#include <fstream>

namespace SSBL {
enum class LogLevel: int {
    NON = 0b0000,
    INF = 0b0001,
    WRN = 0b0010,
    ERR = 0b0100,
    FTL = 0b1000,
    ALL = 0b1111
};

LogLevel operator|(LogLevel a, LogLevel b);
LogLevel operator&(LogLevel a, LogLevel b);
LogLevel operator~(LogLevel a);

String LogLevelToString(LogLevel level);
Color LogLevelToColor(LogLevel level);

struct LoggerSettings {
    explicit LoggerSettings(bool useColor = false, bool showTimestamp = false,
        const String &timeFormat = String("%Y-%m-%d %D %H:%M:%S"));

    bool useColor = false;
    bool showTimestamp = true;
    String timeFormat = "%Y-%m-%d %D %H:%M:%S";
};

struct FileSettings {
    enum FileOutputType { None = 0, SingleFile, RotatingFile };

    explicit FileSettings(FileOutputType fileOutputType = SingleFile,
        const String &outputFilepath = "Log.log", size_t maxRotatingFileSize = 0);

    FileOutputType fileOutputType = SingleFile;
    String outputFilepath = "Log.log";
    size_t maxRotatingFileSize = 0;
};

struct File {
    std::fstream file;
    String filePath;

    size_t GetSize() const;
};

class Logger;

class LoggerStream {
public:
    explicit LoggerStream(LogLevel level = LogLevel::INF);
    ~LoggerStream();

    LoggerStream &operator<<(const String &string);

private:
    LogLevel m_level;
};

class OutputStream final : public std::streambuf {
public:
    explicit OutputStream(LogLevel level = LogLevel::INF);

protected:
    int overflow(int character) override;
    std::streamsize xsputn(const char *string, std::streamsize size) override;

private:
    LogLevel m_level;
};

class Logger {
public:
    static LogLevel levelsVisible;

    static void Init(const LoggerSettings &settings = LoggerSettings());
    static void Init(
        const FileSettings &fileSettings, const LoggerSettings &settings = LoggerSettings());
    static void Destroy();

    static LoggerStream Log(LogLevel level);

    static inline LoggerStream LogInfo();
    static inline LoggerStream LogWarn();
    static inline LoggerStream LogError();
    static inline LoggerStream LogFatal();

    static void UseColor(bool useColor);
    static void ShowTimestamp(bool showTimestamp);
    static void SetTimeFormat(const String &timeFormat);
    static void Set(const LoggerSettings &settings);
    static void SetFile(const FileSettings &settings);

    static void Insert(const String &string);
    static void Flush(LogLevel level = LogLevel::INF);

private:
    static LoggerSettings m_settings;
    static FileSettings m_fileSettings;

    static String m_buffer;
    static size_t m_insertCount;

    static File m_file;
    static size_t m_fileIndex;

    static OutputStream m_logOutStream;
    static OutputStream m_errOutStream;

    static std::streambuf *m_cout;
    static std::streambuf *m_cerr;

    static bool m_isInitialized;

    static std::ostream GetOutStream(LogLevel level);
    static void SetOutputFile(const String &filePath);
    static String FormatRotatingFilePath(const String &filePath);
};

inline LoggerStream Logger::LogInfo() {
    return Log(LogLevel::INF);
}

inline LoggerStream Logger::LogWarn() {
    return Log(LogLevel::WRN);
}

inline LoggerStream Logger::LogError() {
    return Log(LogLevel::ERR);
}

inline LoggerStream Logger::LogFatal() {
    return Log(LogLevel::FTL);
}
} // namespace SSBL