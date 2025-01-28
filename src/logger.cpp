#include "logger.hpp"

#include <chrono>
#include <iostream>
#include <sstream>

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

Logger::LoggerStream::LoggerStream(const LogLevel level)
: messageLogLevel(level) {
}

Logger::LoggerStream::~LoggerStream() {
    if (!(static_cast<char>(logLevel) & static_cast<char>(messageLogLevel))) return;

    std::ostringstream message;

    if (showTimestamp)
        message << getTimestamp() << ' ';

    message << logLevelToString(messageLogLevel) << ' ' << strStream.str() << std::endl;

    if (messageLogLevel == LogLevel::FATAL || messageLogLevel == LogLevel::ERROR) {
        std::cerr << message.str();
    } else {
        std::cout << message.str();
    }
}

Logger::LoggerStream Logger::log(const LogLevel level) {
    return LoggerStream(level);
}