# SSBL (Simple Stream-Based Logger)

A very simple stream-based logger.\
Supports logging to files, log levels (Info, Warning, Error and Fatal), timestamps and limited formatting

## Building from Source

Make sure you have a C++ compiler and CMake and run the following commands:

```sh
cmake -B ./build -S ./
cmake --build ./build
```

***Note:*** only Clang is supported though any other compiler *should* work.

## Example

```cpp
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
logger.LogFatal() << "Hello, Fatal!\n";

// Formatted output
logger.Log() << "My name is {}, and I am {} years old." << "John" << 35 << '\n';
logger.Log() << "{2}, {1}!" << "World" << "Hello" << '\n';

// File output
logger.LogToFile("Example.log") << "Hello, File!\n";
```
