#include "Convert.hpp"

namespace SSBL {
std::optional<size_t> CharToSize(const char character) {
    if (character >= '0' && character <= '9')
        return character - '0';

    return std::nullopt;
}
} // namespace SSBL