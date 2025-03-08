#include "String.hpp"

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

namespace SSBL {
String String::Empty() {
    return "";
}

String::String() = default;

std::string String::ToStdString() const {
    return m_string;
}

String::operator std::string() const {
    return ToStdString();
}

const char *String::ToCString() const {
    return m_string.c_str();
}

String::operator const char *() const {
    return ToCString();
}

bool String::IsEmpty() const {
    return m_string.empty();
}

size_t String::GetLength() const {
    return m_string.length();
}

bool String::Contains(const char character) const {
    return FindFirst(character) != std::nullopt;
}

bool String::Contains(const String &string) const {
    return FindFirst(string) != std::nullopt;
}

std::vector<size_t> String::FindAll(const char query) const {
    std::vector<size_t> occurrences;

    size_t pos = m_string.find(query, 0);
    while (pos != std::string::npos) {
        occurrences.push_back(pos);
        pos = m_string.find(query, pos + 1);
    }

    return occurrences;
}

std::vector<size_t> String::FindAll(const String &query) const {
    std::vector<size_t> occurrences;

    size_t pos = m_string.find(query.m_string, 0);
    while (pos != std::string::npos) {
        occurrences.push_back(pos);
        pos = m_string.find(query.m_string, pos + 1);
    }

    return occurrences;
}

std::optional<size_t> String::Find(const char query, const size_t occurrence) const {
    return FindAll(query)[occurrence];
}

std::optional<size_t> String::Find(const String &query, const size_t occurrence) const {
    return FindAll(query)[occurrence];
}

String String::GetSubstring(const size_t start, const size_t end) const {
    return m_string.substr(start, end - start);
}

void String::Clear() {
    m_string.clear();
}

String &String::Append(const String &string) {
    m_string.append(string.m_string);
    return *this;
}

String &String::Append(const char character) {
    m_string.append(1, character);
    return *this;
}

String &String::Prepend(const char character) {
    m_string.insert(0, 1, character);
    return *this;
}

String &String::Insert(const size_t index, const String &string) {
    m_string.insert(index, string.m_string);

    return *this;
}

String &String::Insert(const size_t index, const char character) {
    m_string.insert(index, 1, character);

    return *this;
}

String &String::Envelope(const String &start, const String &end) {
    Prepend(start);
    return Append(end);
}

String &String::Envelope(const char start, const char end) {
    Prepend(start);
    return Append(end);
}

String &String::ReplaceFirst(const String &query, const String &replace) {
    std::optional<size_t> firstOccurrence = FindFirst(query);
    if (!firstOccurrence.has_value())
        return *this;
    m_string.replace(firstOccurrence.value(), query.GetLength(), replace.m_string);
    return *this;
}

String &String::ReplaceFirst(const char query, const char replace) {
    std::optional<size_t> firstOccurrence = FindFirst(query);
    if (!firstOccurrence.has_value())
        return *this;

    m_string[firstOccurrence.value()] = replace;

    return *this;
}

String &String::ReplaceAll(const String &query, const String &replace) {
    const std::vector<size_t> occurrences = FindAll(query);
    const int charDiff = static_cast<int>(replace.GetLength()) - query.GetLength();
    size_t replaceCount = 0;

    for (const auto &occurrence : occurrences) {
        m_string.replace(occurrence + replaceCount * charDiff, query.GetLength(), replace.m_string);
        replaceCount++;
    }

    return *this;
}

String &String::ReplaceAll(const char query, const char replace) {
    std::vector<size_t> occurrences = FindAll(query);
    for (const auto &occurrence : occurrences) {
        m_string[occurrence] = replace;
    }

    return *this;
}

String &String::RemoveFirst(const String &query) {
    return ReplaceFirst(query, "");
}

String &String::RemoveFirst(const char query) {
    return ReplaceFirst(String(query), "");
}

String &String::RemoveAll(const String &query) {
    return ReplaceAll(query, "");
}

String &String::RemoveAll(const char query) {
    return ReplaceAll(String(query), "");
}

String &String::Prepend(const String &string) {
    m_string.insert(0, string.m_string);
    return *this;
}

std::optional<size_t> String::FindFirst(const char query) const {
    if (size_t pos = m_string.find(query); pos == std::string::npos) {
        return std::nullopt;
    } else {
        return pos;
    }
}

std::optional<size_t> String::FindFirst(const String &query) const {
    if (size_t pos = m_string.find(query.m_string); pos == std::string::npos) {
        return std::nullopt;
    } else {
        return pos;
    }
}

String String::operator+(const String &string) const {
    return {this->m_string + string.m_string};
}

String String::operator+(const char character) const {
    return {this->m_string + character};
}

String &String::operator+=(const String &string) {
    return Append(string);
}

String &String::operator+=(const char character) {
    return Append(character);
}

char &String::operator[](const size_t index) {
    return m_string[index];
}
} // namespace SSBL