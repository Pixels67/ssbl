#include "logger.hpp"

int main() {
    using namespace Logger;

    // Color (off by default)
    useColor = true;

    // Log levels
    log(LogLevel::Info)    << "Hello, Info!";
    log(LogLevel::Warning) << "Hello, Warning!";
    log(LogLevel::Error)   << "Hello, Error!";
    // log(LogLevel::Fatal)   << "Hello, Fatal!";
    // ^ Try and uncomment this

    // Formatted output
    log(LogLevel::Info) << "My name is {}, and I am {} years old." << "John" << 35;
    log(LogLevel::Info) << "{1}, {2}!" << "World" << "Hello";

    // Output to file
    logToFile(LogLevel::Info, "Example.log") << "Hello, Info!";
}