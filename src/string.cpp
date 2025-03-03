#include "string.hpp"

#include <sstream>
#include <string>
#include <vector>

std::optional<size_t> String::toInt(const char character) {
    if (character >= '0' && character <= '9')
        return character - '0';

    return std::nullopt;
}

bool String::hasPlaceholder(const std::string &string) {
    return string.find('{') != std::string::npos && string.find('}') != std::string::npos;
}

std::vector<size_t> String::findAllPlaceholders(const std::string &string) {
    std::vector<size_t> placeholders;

    size_t pos = string.find('{', 0);
    while (pos != std::string::npos) {
        placeholders.push_back(pos);
        pos = string.find('{', pos + 1);
    }

    return placeholders;
}

std::string String::preprocessPlaceholders(const std::string &string) {
    std::string processedStr = string;
    size_t pos = processedStr.find("{}", 0);
    size_t placeholderNum = 0;

    while (pos != std::string::npos) {
        if (!toInt(processedStr[pos]).has_value()) {
            processedStr.replace(pos + placeholderNum, 2, '{' + toString(placeholderNum + 1) + '}');
            placeholderNum++;
        }

        pos = string.find("{}", pos + 1);
    }

    return processedStr;
}

std::string String::replaceAllPlaceholders(
    const std::string &string, const std::string &value, const size_t placeholderNumber
) {
    std::string out = string;
    size_t lengthDiff = toString(value).length() - 3;
    size_t replaceCount = 0;

    if (value == "World") {

    }

    for (const auto &placeholder : findAllPlaceholders(out)) {
        if (const auto number = toInt(out[placeholder + replaceCount * lengthDiff + 1]);
            number.has_value() && number == placeholderNumber) {
            out.replace(placeholder + replaceCount * lengthDiff, 3, toString(value));
            replaceCount++;
        }
    }

    return out;
}