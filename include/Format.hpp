#pragma once

#include "String.hpp"

namespace SSBL {
String IndexEmptyPlaceholders(const String &string);
String Format(const String &string, const String& insertString, size_t index = 1);
} // namespace SSBL