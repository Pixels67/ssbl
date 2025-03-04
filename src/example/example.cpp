#include "Logger.hpp"

int main() {
    using namespace SSBL;

    Logger logger;

    // Configuration (color and timestamp)
    logger.SetConfig(Config::All);

    // Timestamp formatting
    logger.SetTimestampFormat("%h:%m:%s");

    // Log levels
    logger.Log()      << "Hello, Info!\n";
    logger.LogWarn()  << "Hello, Warning!\n";
    logger.LogError() << "Hello, Error!\n";
    // logger.LogFatal() << "Hello, Fatal!\n";
    // ^ Try and uncomment this

    // Formatted output
    logger.Log() << "My name is {}, and I am {} years old." << "John" << 35 << '\n';
    logger.Log() << "{2}, {1}!" << "World" << "Hello" << '\n';

    // File output
    logger.LogToFile("Example.log") << "Hello, File!\n";
}