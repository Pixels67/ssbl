#include "logger.hpp"

int main() {
    using namespace Logger;
    useColor = true;
    log(LogLevel::Error)   << "Hello, Error!";
    log(LogLevel::Warning) << "Hello, Warning!";
    log(LogLevel::Info)    << "Hello, Info!";
    // log(LogLevel::Fatal)   << "Hello, Fatal!";
    logToFile(LogLevel::Info, "Example.log") << "Hello, Info!";
}