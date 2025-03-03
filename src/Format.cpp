#include "Format.hpp"
#include "Convert.hpp"
#include "Logger.hpp"

namespace SSBL {

std::string WithPadding(const std::string &string) {
    return '[' + string + "] ";
}

bool ContainsPlaceholder(const std::string &string) {
    return Contains(string, "{") && Contains(string, "}");
}

std::string IndexPlaceholders(const std::string &string) {
    std::string processedStr = string;
    size_t pos = processedStr.find("{}", 0);
    size_t placeholderNum = 0;

    while (pos != std::string::npos) {
        if (!CharToSize(processedStr[pos]).has_value()) {
            processedStr
                .replace(pos + placeholderNum, 2, '{' + GenericToString(placeholderNum + 1) + '}');
            placeholderNum++;
        }

        pos = string.find("{}", pos + 1);
    }

    return processedStr;
}

} // namespace SSBL