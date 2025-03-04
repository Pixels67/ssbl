#pragma once

#include <optional>
#include <sstream>
#include <string>

namespace SSBL {
template<typename T>
std::string GenericToString(const T &generic) {
    std::stringstream ss;
    ss << generic;
    return ss.str();
}

std::optional<size_t> CharToSize(char character);
} // namespace SSBL