#pragma once

#include <optional>
#include <sstream>
#include <vector>

namespace SSBL {
class String {
public:
    static String Empty();

    String();

    template<typename T>
    String(const T &arg) {
        std::stringstream stringStream;
        stringStream << arg;
        m_string = stringStream.str();
    }

    // Conversions
    [[nodiscard]] std::string ToStdString() const;
    [[nodiscard]] operator std::string() const;

    [[nodiscard]] const char *ToCString() const;
    [[nodiscard]] operator const char *() const;

    // Utility Methods
    [[nodiscard]] bool IsEmpty() const;

    [[nodiscard]] size_t GetLength() const;

    [[nodiscard]] bool Contains(char character) const;
    [[nodiscard]] bool Contains(const String &string) const;

    [[nodiscard]] std::vector<size_t> FindAll(char query) const;
    [[nodiscard]] std::vector<size_t> FindAll(const String &query) const;

    [[nodiscard]] std::optional<size_t> FindFirst(char query) const;
    [[nodiscard]] std::optional<size_t> FindFirst(const String &query) const;

    [[nodiscard]] std::optional<size_t> Find(char query, size_t occurrence) const;
    [[nodiscard]] std::optional<size_t> Find(const String &query, size_t occurrence) const;

    [[nodiscard]] String GetSubstring(size_t start, size_t end) const;

    void Clear();

    String &Append(const String &string);
    String &Append(char character);

    String &Prepend(const String &string);
    String &Prepend(char character);

    String &Insert(size_t index, const String &string);
    String &Insert(size_t index, char character);

    String &Envelope(const String &start, const String &end);
    String &Envelope(char start, char end);

    String &ReplaceFirst(const String &query, const String &replace);
    String &ReplaceFirst(char query, char replace);

    String &ReplaceAll(const String &query, const String &replace);
    String &ReplaceAll(char query, char replace);

    String &RemoveFirst(const String &query);
    String &RemoveFirst(char query);

    String &RemoveAll(const String &query);
    String &RemoveAll(char query);

    String operator+(const String &string) const;
    String operator+(char character) const;

    String &operator+=(const String &string);
    String &operator+=(char character);

    char &operator[](size_t index);

private:
    std::string m_string;
};
} // namespace SSBL