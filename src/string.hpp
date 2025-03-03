#pragma once

#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace String {

template<typename T>
std::string toString(const T &value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

std::optional<size_t> toInt(char character);

bool hasPlaceholder(const std::string &string);

std::vector<size_t> findAllPlaceholders(const std::string &string);

std::string preprocessPlaceholders(const std::string &string);

std::string replaceAllPlaceholders(
    const std::string &string, const std::string &value, size_t placeholderNumber = 1);

template<typename T>
std::string formatString(const std::string &string, const T &value, const size_t insertNumber) {
    if (!hasPlaceholder(string))
        return string + toString(value);

    std::string out = preprocessPlaceholders(string);
    out = replaceAllPlaceholders(out, toString(value), insertNumber);

    return out;
}

} // namespace String