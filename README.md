# Logger

Simple stream-based logger.

## Building from Source

Make sure CMake is installed and run the following commands:

```sh
cmake -B ./build -S ./
cmake --build ./build
```

## Example

```cpp
using namespace Logger;

// Color (off by default)
useColor = true;

// Log levels
log(LogLevel::Info)    << "Hello, Info!";
log(LogLevel::Warning) << "Hello, Warning!";
log(LogLevel::Error)   << "Hello, Error!";
log(LogLevel::Fatal)   << "Hello, Fatal!";

// Formatted output
log(LogLevel::Info) << "My name is {}, and I am {} years old." << "John" << 35;
log(LogLevel::Info) << "{2}, {1}!" << "World" << "Hello";

// Output to file
logToFile(LogLevel::Info, "Example.log") << "Hello, Info!";
```
