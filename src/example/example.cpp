#include "logger.hpp"

int main() {
    Logger::log(LogLevel::FATAL)   << "Hello, Fatal!";
    Logger::log(LogLevel::ERROR)   << "Hello, Error!";
    Logger::log(LogLevel::WARNING) << "Hello, Warning!";
    Logger::log(LogLevel::INFO)    << "Hello, Info!";
}