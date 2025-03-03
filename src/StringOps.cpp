#include "StringOps.hpp"

#include <vector>

namespace SSBL {
bool Contains(const std::string &string, const std::string &query) {
    return string.find(query) != std::string::npos;
}

std::vector<size_t> FindAll(const std::string &string, const std::string &query) {
    std::vector<size_t> occurrences;

    size_t pos = string.find(query, 0);
    while (pos != std::string::npos) {
        occurrences.push_back(pos);
        pos = string.find(query, pos + 1);
    }

    return occurrences;
}

std::string ReplaceAll(
    const std::string &string, const std::string &substring, const std::string &replacement) {
    std::string out = string;
    const size_t lengthDiff = replacement.length() - substring.length();
    size_t replaceCount = 0;

    for (const auto toReplace : FindAll(out, substring)) {
        out.replace(toReplace + replaceCount * lengthDiff, substring.length(), replacement);
        replaceCount++;
    }

    return out;
}
}