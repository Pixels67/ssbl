#pragma once

#include "Convert.hpp"
#include "StringOps.hpp"
#include <sstream>
#include <string>

namespace SSBL {

std::string WithPadding(const std::string &string);

bool ContainsPlaceholder(const std::string &string);
std::string IndexPlaceholders(const std::string &string);

template<typename T>
std::string Format(const std::string &string, const T &value, const size_t insertNumber) {
    if (!ContainsPlaceholder(string))
        return string + GenericToString(value);

    std::string out = IndexPlaceholders(string);
    const std::string placeholder = "{" + std::to_string(insertNumber) + "}";

    out = ReplaceAll(out, placeholder, GenericToString(value));
    out = ReplaceAll(out, "\n", "");

    if (const size_t pos = out.find('\n'); pos != std::string::npos)
        out.replace(pos, 1, "");

    return out;
}

} // namespace SSBL