#include "Format.hpp"

#include "Convert.hpp"
#include <vector>

namespace SSBL {
String IndexEmptyPlaceholders(const String &string) {
    String indexed = string;
    std::vector<size_t> placeholders = indexed.FindAll('{');
    size_t index = 1;

    for (const auto placeholder : placeholders) {
        size_t actualIndex = placeholder + index;

        if (!CharToSize(indexed[actualIndex]).has_value()) {
            indexed.Insert(actualIndex, String(index)[0]);
            index++;
        }
    }

    return indexed;
}

String Format(const String &string, const String &insertString, const size_t index) {
    if (insertString.IsEmpty())
        return string;
    const String placeholder = String(index).Envelope('{', '}');
    String formatted = IndexEmptyPlaceholders(string);

    if (!formatted.Contains(placeholder))
        return string + insertString;

    formatted.ReplaceAll(placeholder, insertString);

    return formatted;
}
} // namespace SSBL