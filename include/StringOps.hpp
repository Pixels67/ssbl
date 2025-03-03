#pragma once

#include <string>
#include <vector>

namespace SSBL {
bool Contains(const std::string &string, const std::string &query);
std::vector<size_t> FindAll(const std::string &string, const std::string &query);
std::string ReplaceAll(
    const std::string &string, const std::string &substring, const std::string &replacement);
} // namespace SSBL