#include "Console.hpp"

#include "Format.hpp"
#include "Logger.hpp"
#include "String.hpp"
#include <ostream>

#if defined _WIN32

#include <windows.h>

#endif

namespace SSBL {
String ColorToAnsiEscapeCode(const Color color, const bool bold) {
    if (bold) {
        return Format("\033[1;{}m", static_cast<int>(color));
    }

    return Format("\033[0;{}m", static_cast<int>(color));
}

void SetColor(Color color, std::ostream &output, const bool bold) {
#if defined _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(color));
#else
    output << ColorToAnsiEscapeCode(color, bold);
#endif
}

void ResetColor(std::ostream &output) {
#if defined _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(Color::DEFAULT));
#else
    output << ColorToAnsiEscapeCode(Color::DEFAULT);
#endif
}
} // namespace SSBL