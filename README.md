# SSBL (Simple Stream-Based Logger)

A very simple stream-based logger.\
Supports logging to files, log levels (Info, Warning, Error and Fatal), timestamps and limited formatting

## Building from Source

Make sure you have a C++ compiler and CMake and run the following commands:

```sh
cmake -B ./build -S ./
cmake --build ./build
```

## Examples
Basic functionality:

```cpp
using namespace SSBL;

// Pass custom settings, otherwise load default settings
Logger::Init();

// Configuration
Logger::UseColor(true);
Logger::levelsVisible = LogLevel::INF | LogLevel::ERR;
Logger::ShowTimestamp(true);
Logger::SetTimeFormat("%Y-%m-%d %D %H:%M:%S");

// Log levels
Logger::LogInfo()  << "Hello, Info!";
Logger::LogWarn()  << "Hello, Warning!";
Logger::LogError() << "Hello, Error!";
Logger::LogFatal() << "Hello, Fatal!";

// Formatted output
Logger::LogInfo() << "My name is {}, and I am {} years old." << "John" << 35;
Logger::LogInfo() << "{2}, {1}!" << "World" << "Hello";

Logger::Destroy();
```
File output:
```cpp
using namespace SSBL;

// Single file
Logger::Init(FileSettings(FileSettings::SingleFile, "name.log"))

// Rotating files with 64 bytes max size, %x is a unique index, time placeholders can be used
Logger::Init(FileSettings(FileSettings::RotatingFile, "%x.log", 64));
```
