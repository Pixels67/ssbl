#include "Logger.hpp"

int main() {
    SSBL::Logger logger("Example.log");

    logger
        .UseColor(true)
        .SetTimeFormat("%Y-%m-%d %H:%M:%S");

    logger.Log()      << "Info";
    logger.LogWarn()  << "Warning";
    logger.LogError() << "Error";

    logger.Log() << "My name is {} and I'm {} years old." << "John" << 35;
    logger.Log() << "{2}, {1}!" << "World" << "Hello";
}