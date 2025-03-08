#include "Logger.hpp"
#include <iostream>

int main() {
    SSBL::Logger logger;

    logger
        .UseColor(true)
        .EnableRotatingFiles("%x", 128);

    logger.Log()      << "Info";
    logger.LogWarn()  << "Warning";
    logger.LogError() << "Error";

    std::cout << "cout" << std::endl;

    logger.Log() << "My name is {}, and I'm {} years old." << "John" << 35;
    logger.Log() << "My name is {2}, {1} {2}." << "James" << "Bond";
}