#include "Logger.hpp"

#include "Console.hpp"
#include "Format.hpp"
#include "String.hpp"
#include "Time.hpp"
#include <cassert>
#include <fstream>
#include <iostream>

namespace SSBL {

LogLevel operator|(LogLevel a, LogLevel b) {
    return static_cast<LogLevel>(static_cast<int>(a) | static_cast<int>(b));
}

LogLevel operator&(LogLevel a, LogLevel b) {
    return static_cast<LogLevel>(static_cast<int>(a) & static_cast<int>(b));
}

LogLevel operator~(LogLevel a) {
    return static_cast<LogLevel>(~static_cast<int>(a));
}

String LogLevelToString(const LogLevel level) {
    switch (level) {
    case LogLevel::INF:
        return "INF";
    case LogLevel::WRN:
        return "WRN";
    case LogLevel::ERR:
        return "ERR";
    case LogLevel::FTL:
        return "FTL";
    default:
        return "UNK";
    }
}

Color LogLevelToColor(const LogLevel level) {
    switch (level) {
    case LogLevel::INF:
        return Color::BLUE;
    case LogLevel::WRN:
        return Color::YELLOW;
    case LogLevel::ERR:
        return Color::RED;
    case LogLevel::FTL:
        return Color::RED;
    default:
        return Color::DEFAULT;
    }
}

size_t File::GetSize() const {
    return std::filesystem::file_size(filePath.ToStdString());
}

LoggerStream::LoggerStream(const LogLevel level)
    : m_level(level) {}

LoggerStream::~LoggerStream() {
    Logger::Flush(m_level);
}

LoggerStream &LoggerStream::operator<<(const String &string) {
    Logger::Insert(string);
    return *this;
}

OutputStream::OutputStream(const LogLevel level)
    : m_level(level) {}

int OutputStream::overflow(const int character) {
    if (character == EOF)
        return character;

    const char ch = static_cast<char>(character);
    String str(ch);
    Logger::Insert(String(ch));

    return character;
}

std::streamsize OutputStream::xsputn(const char *string, const std::streamsize size) {
    const String str(std::string(string, size));
    if (size == 1) {
        overflow(str[0]);
        return size;
    }

    Logger::Insert(String(str));
    if (str.Contains('\n')) {
        Logger::Flush(m_level);
    }

    return size;
}

LogLevel Logger::levelsVisible = LogLevel::ALL;

LoggerSettings Logger::m_settings = LoggerSettings();
FileSettings Logger::m_fileSettings = FileSettings();

std::streambuf *Logger::m_cout;
std::streambuf *Logger::m_cerr;

String Logger::m_buffer;
size_t Logger::m_insertCount = 0;

File Logger::m_file = File();
size_t Logger::m_fileIndex = 0;

OutputStream Logger::m_logOutStream = OutputStream(LogLevel::INF);
OutputStream Logger::m_errOutStream = OutputStream(LogLevel::ERR);

bool Logger::m_isInitialized = false;

void Logger::Init(const LoggerSettings &settings) {
    assert(!m_isInitialized);
    m_settings = settings;

    // Save the actual cout and cerr buffers
    m_cout = std::cout.rdbuf();
    m_cerr = std::cerr.rdbuf();

    // Redirect cout and cerr
    std::cout.rdbuf(&m_logOutStream);
    std::cerr.rdbuf(&m_errOutStream);

    // ReSharper disable once CppIncompleteSwitchStatement
    // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
    switch (m_fileSettings.fileOutputType) {
    case FileSettings::SingleFile:
        SetOutputFile(m_fileSettings.outputFilepath.ToStdString());
        break;
    case FileSettings::RotatingFile:
        const String filePath = FormatRotatingFilePath(m_fileSettings.outputFilepath).ToStdString();
        SetOutputFile(filePath);
        break;
    }

    m_isInitialized = true;
}

void Logger::Init(const FileSettings &fileSettings, const LoggerSettings &settings) {
    m_fileSettings = fileSettings;

    Init(settings);
}

void Logger::Destroy() {
    m_file.file.close();
    m_isInitialized = false;
}

LoggerStream Logger::Log(const LogLevel level) {
    return LoggerStream(level);
}

void Logger::UseColor(const bool useColor) {
    m_settings.useColor = useColor;
}

void Logger::ShowTimestamp(const bool showTimestamp) {
    m_settings.showTimestamp = showTimestamp;
}

void Logger::SetTimeFormat(const String &timeFormat) {
    m_settings.timeFormat = timeFormat;
}

void Logger::Set(const LoggerSettings &settings) {
    m_settings = settings;
}

void Logger::SetFile(const FileSettings &settings) {
    m_fileSettings = settings;
}

void Logger::Insert(const String &string) {
    String str(string);

    m_buffer = Format(m_buffer, str.RemoveAll('\n'), m_insertCount);
    m_insertCount++;
}

void Logger::Flush(const LogLevel level) {
    if (!static_cast<bool>(level & levelsVisible)) {
        m_buffer.Clear();
        m_insertCount = 0;
        return;
    }

    std::ostream ostream = GetOutStream(level);

    String str(m_buffer);
    str.Prepend(LogLevelToString(level).Envelope("[", "] "));

    if (m_settings.showTimestamp) {
        str.Prepend(GetTimestamp(m_settings.timeFormat).Envelope("[", "] "));
    }

    if (m_fileSettings.fileOutputType == FileSettings::SingleFile) {
        m_file.file << str << std::endl;
    } else if (m_fileSettings.fileOutputType == FileSettings::RotatingFile) {
        if (m_file.GetSize() > m_fileSettings.maxRotatingFileSize) {
            const String filePath = FormatRotatingFilePath(m_fileSettings.outputFilepath);
            SetOutputFile(filePath);
        }

        m_file.file << str << std::endl;
    }

    if (m_settings.useColor) {
        SetColor(LogLevelToColor(level), ostream, level == LogLevel::FTL);
    }

    ostream << str << std::endl;

    if (m_settings.useColor) {
        ResetColor(ostream);
    }

    m_buffer.Clear();
    m_insertCount = 0;
}

std::ostream Logger::GetOutStream(const LogLevel level) {
    std::streambuf *streambuf;

    if (level == LogLevel::ERR || level == LogLevel::FTL) {
        streambuf = m_cerr;
    } else {
        streambuf = m_cout;
    }

    return std::ostream(streambuf);
}

void Logger::SetOutputFile(const String &filePath) {
    m_file.file.close();
    m_file.file.open(filePath.ToStdString(), std::ios::out);
    m_file.filePath = filePath.ToStdString();
    assert(m_file.file.is_open());
}

String Logger::FormatRotatingFilePath(const String &filePath) {
    m_fileIndex++;
    return GetTimestamp(filePath).ReplaceAll("%x", String(m_fileIndex)).ToStdString();
}
} // namespace SSBL