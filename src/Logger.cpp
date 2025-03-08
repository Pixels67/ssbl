#include "Logger.hpp"

#include "Console.hpp"
#include "Format.hpp"
#include "String.hpp"
#include "Time.hpp"
#include <filesystem>
#include <iostream>

namespace SSBL {

std::optional<std::streambuf *> Logger::cout = std::nullopt;
std::optional<std::streambuf *> Logger::cerr = std::nullopt;

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

LoggerStream::LoggerStream(Logger &logger)
    : m_logger(logger) {}

LoggerStream::~LoggerStream() {
    m_logger.Flush();
}

LoggerStream &LoggerStream::operator<<(const String &string) {
    m_logger << string;
    return *this;
}

Logger::Logger(LoggerSettings settings, const String &outputFile)
    : m_settings(std::move(settings)) {
    if (!outputFile.IsEmpty()) {
        m_file.open(outputFile.ToStdString());
    }

    if (!cout.has_value()) {
        cout = std::make_optional<std::streambuf *>(std::cout.rdbuf());
    }

    if (!cerr.has_value()) {
        cerr = std::make_optional<std::streambuf *>(std::cerr.rdbuf());
    }

    std::cout.rdbuf(this);
    std::cerr.rdbuf(this);
}

Logger::Logger(const String &outputFile) {
    if (!outputFile.IsEmpty()) {
        m_file.open(outputFile.ToStdString());
    }

    if (!cout.has_value()) {
        cout = std::make_optional<std::streambuf *>(std::cout.rdbuf());
    }

    if (!cerr.has_value()) {
        cerr = std::make_optional<std::streambuf *>(std::cerr.rdbuf());
    }

    std::cout.rdbuf(this);
    std::cerr.rdbuf(this);
}

Logger::~Logger() {
    if (m_file.is_open()) {
        m_file.close();
    }
}

LoggerStream Logger::Log(const LogLevel level) {
    m_currentLevel = level;
    return LoggerStream(*this);
}

LoggerStream Logger::LogWarn() {
    return Log(LogLevel::WRN);
}

LoggerStream Logger::LogError() {
    return Log(LogLevel::ERR);
}

LoggerStream Logger::LogFatal() {
    return Log(LogLevel::FTL);
}

Logger &Logger::UseColor(const bool useColor) {
    m_settings.useColor = useColor;
    return *this;
}

Logger &Logger::ShowTimestamp(const bool showTimestamp) {
    m_settings.showTimestamp = showTimestamp;
    return *this;
}

Logger &Logger::SetTimeFormat(const String &timeFormat) {
    m_settings.timeFormat = timeFormat;
    return *this;
}

Logger &Logger::EnableRotatingFiles(const String &format, const size_t sizeLimitBytes) {
    m_rotatingFiles = true;
    m_rotatingFileFormat = format;
    m_rotatingFileSize = sizeLimitBytes;
    return *this;
}

Logger &Logger::DisableRotatingFiles() {
    m_rotatingFiles = false;
    return *this;
}

Logger &Logger::SetOutputFile(const String &fileName) {
    m_file.open(fileName.ToStdString());
    return *this;
}

void Logger::operator<<(const String &string) {
    m_stream = Format(m_stream, string, m_insertCount);
    m_insertCount++;

    if (string.Contains('\n')) {
        m_stream.RemoveFirst('\n');
        Flush();
    }
}

void Logger::Flush() {
    std::streambuf *outputBuffer = m_currentLevel == LogLevel::FTL || m_currentLevel == LogLevel::ERR
                                    ? cerr.value()
                                    : cout.value();
    std::ostream outputStream(outputBuffer);

    if (m_settings.useColor) {
        SetColor(LogLevelToColor(m_currentLevel), outputStream, m_currentLevel == LogLevel::FTL);
    }

    ProcessStream();
    outputStream << m_stream << std::endl;

    if (m_file.is_open()) {
        m_file << m_stream << std::endl;
    }

    if (m_rotatingFiles) {
        UpdateRotatingFiles();
        m_rotatingFile << m_stream << std::endl;
    }

    // Reset
    if (m_settings.useColor) {
        ResetColor(outputStream);
    }

    m_stream.Clear();
    m_insertCount = 0;

    if (m_currentLevel == LogLevel::FTL) {
        std::exit(EXIT_FAILURE);
    }
}

int Logger::overflow(const int character) {
    if (character != EOF) {
        const LogLevel previousLevel = m_currentLevel;
        m_currentLevel = LogLevel::NON;
        const char ch = static_cast<char>(character);
        *this << String(ch);
        m_currentLevel = previousLevel;
    }

    return character;
}

std::streamsize Logger::xsputn(const char *string, const std::streamsize size) {
    const LogLevel previousLevel = m_currentLevel;
    m_currentLevel = LogLevel::NON;
    *this << String(string);
    m_currentLevel = previousLevel;
    return size;
}

void Logger::UpdateRotatingFiles() {
    const String filename = GetTimestamp(m_rotatingFileFormat)
        .ReplaceAll("%x", m_rotatingFileIndex)
        .Append(".log");

    if (!m_rotatingFile.is_open()) {
        m_filename = filename;
        m_rotatingFile.open(filename.ToStdString());
        m_rotatingFileIndex++;
    }

    if (std::filesystem::file_size(m_filename.ToStdString()) > m_rotatingFileSize) {
        m_rotatingFile.close();
        m_filename = filename;
        m_rotatingFile.open(m_filename.ToStdString());
        m_rotatingFileIndex++;
    }
}

void Logger::ProcessStream() {
    const String LogLevel = LogLevelToString(m_currentLevel).Envelope("[", "] ");
    const String Timestamp = GetTimestamp(m_settings.timeFormat).Envelope("[", "] ");

    m_stream.Prepend(LogLevel);
    if (m_settings.showTimestamp) {
        m_stream.Prepend(Timestamp);
    }
}
} // namespace SSBL