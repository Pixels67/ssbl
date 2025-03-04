#include "Logger.hpp"
#include "Log.hpp"
#include <fstream>

#if _WIN32

#include <windows.h>

#endif

namespace SSBL {

Logger &Logger::Log(const Level level) {
    m_level = level;
    return *this;
}
Logger &Logger::LogWarn() {
    return Log(Level::Warning);
}

Logger &Logger::LogError() {
    return Log(Level::Error);
}

Logger &Logger::LogFatal() {
    return Log(Level::Fatal);
}

Logger &Logger::LogToFile(const std::string &filePath, Level level) {
    m_level = level;
    m_fileOutStream = std::ofstream(filePath);
    return *this;
}

void Logger::SetOutStream(std::ostream *messageOutStream, std::ostream *errorOutStream) {
    m_msgOutStream = messageOutStream;
    m_errOutStream = errorOutStream;
}

void Logger::SetConfig(const Config &config) {
    m_config = config;
}

void Logger::SetLevelMask(const Level level) {
    m_levelMask = level;
}

bool Logger::IsLevelIncluded(const Level level) const {
    return (static_cast<int>(level) & static_cast<int>(m_levelMask)) != 0;
}

void Logger::Send(const std::string &string) {
    if (m_fileOutStream.has_value()) {
        m_fileOutStream.value() << ToLog(string, m_level, m_config);
        m_fileOutStream.value().close();
        m_fileOutStream.reset();
        return;
    }

    if (static_cast<bool>(m_config & Config::Color))
        SetColor();

    switch (m_level) {
    case Level::Fatal:
        *m_errOutStream << ToLog(string, m_level, m_config);
        std::exit(EXIT_FAILURE);
        break;
    case Level::Error:
        *m_errOutStream << ToLog(string, m_level, m_config);
        break;
    default:
        *m_msgOutStream << ToLog(string, m_level, m_config);
        break;
    }
}

void Logger::Flush() {
    m_stream.str("");
    insertCount = 0;

    if (static_cast<bool>(m_config & Config::Color))
        ResetColor();
}

void Logger::SetColor() {
#if _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GetColor());
#else
        *m_errOutStream << GetColor();
        *m_msgOutStream << GetColor();
#endif
}

void Logger::ResetColor() const {
#if _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
#else
    *m_msgOutStream << "\033[0m";
    *m_errOutStream << "\033[0m";
#endif
}

#if _WIN32

int Logger::GetColor() const {
    switch (m_level) {
    case Level::Fatal:
        return 0x0C; // Red
    case Level::Error:
        return 0x0C; // Red
    case Level::Warning:
        return 0x0E; // Yellow
    case Level::Info:
        return 0x09; // Blue
    default:
        return 0x0F;
    }
}
#else

std::string Logger::GetColor() const {
    switch (m_level) {
    case Level::Fatal:
        return "\033[1;31m"; // Red
    case Level::Error:
        return "\033[0;31m"; // Light red
    case Level::Warning:
        return "\033[0;33m"; // Yellow
    case Level::Info:
        return "\033[0;34m"; // Blue
    default:
        return "\033[0m";
    }
}
#endif

} // namespace SSBL