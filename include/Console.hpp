#pragma once

#include "String.hpp"
#include <ostream>

#if defined _WIN32

#include <windows.h>

#endif

namespace SSBL {
class Logger;

#if defined _WIN32

enum class Color { DEFAULT = 15, RED = 12, YELLOW = 14, BLUE = 9 };

#else

enum class Color { DEFAULT = 0, RED = 31, YELLOW = 33, BLUE = 34 };

#endif

String ColorToAnsiEscapeCode(Color color, bool bold = false);
void SetColor(Color color, std::ostream &output, bool bold = false);
void ResetColor(std::ostream &output);
} // namespace SSBL