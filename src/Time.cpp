#include "Time.hpp"

#include "StringOps.hpp"
#include <chrono>
#include <ctime>

namespace SSBL {
Time::Time(const time_t time) {
    const std::string timeString = std::ctime(&time);

    year   = std::stoi(timeString.substr(20, 4));
    month  = timeString.substr(4, 3);
    day    = std::stoi(timeString.substr(8, 2));

    hour   = std::stoi(timeString.substr(11, 2));
    minute = std::stoi(timeString.substr(14, 2));
    second = std::stoi(timeString.substr(17, 2));
}

std::string Time::AsString(const std::string &format) const {
    std::string result = format;

    result = ReplaceAll(result, "%Y", std::to_string(year));
    result = ReplaceAll(result, "%M", month);
    result = ReplaceAll(result, "%D", std::to_string(day));

    result = ReplaceAll(result, "%h", std::to_string(hour));
    result = ReplaceAll(result, "%m", std::to_string(minute));
    result = ReplaceAll(result, "%s", std::to_string(second));

    return result;
}

std::string Time::GetCurrentTime(const std::string &format) {
    using std::chrono::system_clock;

    const auto currentTime = system_clock::to_time_t(system_clock::now());
    return Time(currentTime).AsString(format);
}
} // namespace SSBL