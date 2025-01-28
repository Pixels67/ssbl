#include "logger.hpp"

#include <chrono>
#include <iostream>
#include <sstream>

#if _WIN32

#include <windows.h>

#endif

std::string Logger::logLevelToString(const LogLevel level) {
    switch (level) {
        case LogLevel::Fatal:   return "[FTL]";
        case LogLevel::Error:   return "[ERR]";
        case LogLevel::Warning: return "[WRN]";
        case LogLevel::Info:    return "[INF]";
        default:
            log(LogLevel::Error) << "Invalid log level specified!";
            return "\0";
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
        case LogLevel::Fatal:   return 0x0C;  // Red
        case LogLevel::Error:   return 0x0C;  // Red
        case LogLevel::Warning: return 0x0E;  // Yellow
        case LogLevel::Info:    return 0x09;  // Blue
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
        case LogLevel::Fatal:   return "\033[1;31m";  // Red
        case LogLevel::Error:   return "\033[0;31m";  // Light red
        case LogLevel::Warning: return "\033[0;33m";  // Yellow
        case LogLevel::Info:    return "\033[0;34m";  // Blue
        default:
            log(LogLevel::Error) << "Invalid log level specified!";
            return "\033[0m";
    }
}

#endif

Logger::LoggerStream::LoggerStream(const LogLevel level)
: messageLogLevel(level) {
}

Logger::LoggerStream::~LoggerStream() {
    if (!(static_cast<char>(logLevel) & static_cast<char>(messageLogLevel))) return;

    std::ostringstream message;

#if _WIN32
    if (useColor)
        setWindowsColor(getColor(messageLogLevel));
#else
    if (useColor)
        message << getColor(messageLogLevel);
#endif

    if (showTimestamp)
        message << getTimestamp() << ' ';

    message << logLevelToString(messageLogLevel) << ' ' << strStream.str() << std::endl;

#if not _WIN32
    if (useColor)
        message << "\033[0m";
#endif

    if (messageLogLevel == LogLevel::Fatal) {
        std::cerr << message.str();
        std::exit(EXIT_FAILURE);
    } else if (messageLogLevel == LogLevel::Error) {
        std::cerr << message.str();
    } else {
        std::cout << message.str();
    }

#if _WIN32
    if (useColor)
        setWindowsColor(0x0F);
#endif
}

Logger::LoggerStream Logger::log(const LogLevel level) {
    return LoggerStream(level);
}