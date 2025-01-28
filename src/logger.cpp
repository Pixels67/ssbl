#include "logger.hpp"

#include <chrono>
#include <iostream>
#include <sstream>

#if _WIN32

#include <windows.h>

#endif

std::string Logger::logLevelToString(const LogLevel level) {
    switch (level) {
        case LogLevel::FATAL:   return "[FTL]";
        case LogLevel::ERROR:   return "[ERR]";
        case LogLevel::WARNING: return "[WRN]";
        case LogLevel::INFO:    return "[INF]";
        default:
            log(LogLevel::ERROR) << "Invalid log level specified!";
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
        case LogLevel::FATAL:   return FOREGROUND_RED | FOREGROUND_INTENSITY;  // Red
        case LogLevel::ERROR:   return FOREGROUND_RED | FOREGROUND_INTENSITY;  // Light red
        case LogLevel::WARNING: return FOREGROUND_RED | FOREGROUND_GREEN;      // Yellow
        case LogLevel::INFO:    return FOREGROUND_GREEN";                      // Green
        default:
            log(LogLevel::ERROR) << "Invalid log level specified!";
        return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}

void setWindowsColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#else

std::string Logger::getColor(const LogLevel level) {
    switch (level) {
        case LogLevel::FATAL:   return "\033[1;31m";  // Red
        case LogLevel::ERROR:   return "\033[0;31m";  // Light red
        case LogLevel::WARNING: return "\033[0;33m";  // Yellow
        case LogLevel::INFO:    return "\033[0;32m";  // Green
        default:
            log(LogLevel::ERROR) << "Invalid log level specified!";
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

#if _WIN32
    if (useColor)
        setWindowsColor(RESET);
#else
    if (useColor)
        message << "\033[0m";
#endif

    if (messageLogLevel == LogLevel::FATAL) {
        std::cerr << message.str();
        std::exit(EXIT_FAILURE);
    } else if (messageLogLevel == LogLevel::ERROR) {
        std::cerr << message.str();
    } else {
        std::cout << message.str();
    }
}

Logger::LoggerStream Logger::log(const LogLevel level) {
    return LoggerStream(level);
}