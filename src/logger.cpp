#include "logger.hpp"

#include <chrono>
#include <iostream>
#include <sstream>

#if _WIN32

#include <windows.h>

#endif

std::string Logger::logLevelToString(const LogLevel level) {
    switch (level) {
    case LogLevel::Fatal:
        return "[FTL]";
    case LogLevel::Error:
        return "[ERR]";
    case LogLevel::Warning:
        return "[WRN]";
    case LogLevel::Info:
        return "[INF]";
    default:
        log(LogLevel::Error) << "Invalid log level specified!";
        return "[UNK]";
    }
}

std::string Logger::getTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto currentTime = std::chrono::system_clock::to_time_t(now);

    std::string currentTimeString = ctime(&currentTime);
    currentTimeString.pop_back();

    return '[' + currentTimeString + ']';
}

#if _WIN32

int Logger::getColor(const LogLevel level) {
    switch (level) {
    case LogLevel::Fatal:
        return 0x0C; // Red
    case LogLevel::Error:
        return 0x0C; // Red
    case LogLevel::Warning:
        return 0x0E; // Yellow
    case LogLevel::Info:
        return 0x09; // Blue
    default:
        log(LogLevel::Error) << "Invalid log level specified!";
        return 0x0F;
    }
}

void Logger::setWindowsColor(const int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#else

std::string Logger::getColor(const LogLevel level) {
    switch (level) {
    case LogLevel::Fatal:
        return "\033[1;31m"; // Red
    case LogLevel::Error:
        return "\033[0;31m"; // Light red
    case LogLevel::Warning:
        return "\033[0;33m"; // Yellow
    case LogLevel::Info:
        return "\033[0;34m"; // Blue
    default:
        log(LogLevel::Error) << "Invalid log level specified!";
        return "\033[0m";
    }
}

#endif

Logger::LogStream::LogStream(const LogLevel level)
    : m_messageLogLevel(level) {}

Logger::LogStream::LogStream(const LogLevel level, const std::string &fileName)
    : m_messageLogLevel(level) {
    m_outFileStream = std::ofstream(fileName);
}

Logger::LogStream::~LogStream() {
    if (!(static_cast<char>(logLevel) & static_cast<char>(m_messageLogLevel)))
        return;

    std::ostringstream message;

#if _WIN32
    if (useColor && !m_outFileStream.has_value())
        setWindowsColor(getColor(m_messageLogLevel));
#else
    if (useColor && !m_outFileStream.has_value())
        message << getColor(m_messageLogLevel);
#endif

    if (showTimestamp)
        message << getTimestamp() << ' ';

    message << logLevelToString(m_messageLogLevel) << ' ' << m_strStream.str() << std::endl;

#if not _WIN32
    if (useColor && !m_outFileStream.has_value())
        message << "\033[0m";
#endif

    if (m_outFileStream.has_value()) {
        m_outFileStream.value() << message.str();
    } else if (m_messageLogLevel == LogLevel::Fatal) {
        std::cerr << message.str();
        std::exit(EXIT_FAILURE);
    } else if (m_messageLogLevel == LogLevel::Error) {
        std::cerr << message.str();
    } else {
        std::cout << message.str();
    }

#if _WIN32
    if (useColor && !m_outFileStream.has_value())
        setWindowsColor(0x0F);
#endif
}

Logger::LogStream Logger::log(const LogLevel level) {
    return LogStream(level);
}

Logger::LogStream Logger::logToFile(const LogLevel level, const std::string &fileName) {
    return {level, fileName};
}