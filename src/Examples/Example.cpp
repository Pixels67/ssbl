#include "Logger.hpp"
#include <iostream>

int main() {
    using namespace SSBL;

    // Initialization & Configuration
    Logger::Init(FileSettings(FileSettings::RotatingFile, "%x.log", 64));
    Logger::UseColor(true);
    Logger::levelsVisible = ~LogLevel::INF;

    // Logging
    Logger::LogInfo()  << "Hello, Info!";
    Logger::LogWarn()  << "Hello, Warning!";
    Logger::LogError() << "Hello, Error!";
    Logger::LogFatal() << "Hello, Fatal!";

    // cout and cerr redirection
    std::cout << "cout\n";
    std::cerr << "cerr\n";

    // Formatting
    Logger::LogInfo() << "My name is {}, and I'm {} years old." << "John" << 35;
    Logger::LogInfo() << "My name is {2}, {1} {2}." << "James" << "Bond";

    // Deinitialization
    Logger::Destroy();
}