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
using namespace SSBL;

Logger logger;
logger.SetConfig(Config::All);

// Log levels
logger.Log(Level::Info) << "Hello, Info!\n";
logger.Log(Level::Warning) << "Hello, Warning!\n";
logger.Log(Level::Error) << "Hello, Error!\n";
logger.Log(Level::Fatal) << "Hello, Fatal!\n";

// Formatted output
logger.Log(Level::Info) << "My name is {}, and I am {} years old." << "John" << 35 << '\n';
logger.Log(Level::Info) << "{2}, {1}!" << "World" << "Hello" << '\n';

// File output
logger.LogToFile("Example.log") << "Hello, File!\n";
```
