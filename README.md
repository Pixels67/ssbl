# SSBL (Simple Stream-Based Logger)

A very simple stream-based logger.\
Supports logging to files, log levels (Info, Warning, Error and Fatal), timestamps and limited formatting

## Building from Source

Make sure you have a C++ compiler and CMake and run the following commands:

```sh
cmake -B ./build -S ./
cmake --build ./build
```

## Example

```cpp
using namespace SSBL;

Logger logger;

// Configuration
logger
    .UseColor(true)
    .ShowTimestamp(true)
    .SetTimeFormat("%Y-%m-%d %H:%M:%S")
    .SetOutputFile("Example.log");

// Log levels
logger.Log()      << "Hello, Info!";
logger.LogWarn()  << "Hello, Warning!";
logger.LogError() << "Hello, Error!";
logger.LogFatal() << "Hello, Fatal!";

// Formatted output
logger.Log() << "My name is {}, and I am {} years old." << "John" << 35;
logger.Log() << "{2}, {1}!" << "World" << "Hello";
```
