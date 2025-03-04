#pragma once

#include <string>

namespace SSBL {

constexpr const char *DEFAULT_FORMAT = "%Y %M %D %h:%m:%s";

struct Time {
    size_t year;
    std::string month;
    size_t day;
    size_t hour;
    size_t minute;
    size_t second;

    explicit Time(time_t time);

    [[nodiscard]] std::string AsString(const std::string &format = DEFAULT_FORMAT) const;
    [[nodiscard]] static std::string GetCurrentTime(const std::string &format  = DEFAULT_FORMAT);
};
} // namespace SSBL