#include "logger.hpp"

int main() {
    Logger::useColor = true;
    // Logger::log(LogLevel::FATAL)   << "Hello, Fatal!";
    Logger::log(LogLevel::Error)   << "Hello, Error!";
    Logger::log(LogLevel::Warning) << "Hello, Warning!";
    Logger::log(LogLevel::Info)    << "Hello, Info!";
}