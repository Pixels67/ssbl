#pragma once

#include <sstream>
#include <string>

namespace String {

template <typename T>
std::string to_string(const T &value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template<typename T>
std::string formatString(const std::string &string, const T &value) {
    if (string.find("{}") == std::string::npos) return string + to_string(value);

    std::string out = string;

    if (size_t pos = out.find("{}"); pos != std::string::npos) {
        return out.replace(pos, 2, to_string(value));
    }

    return out;
}

} // namespace String