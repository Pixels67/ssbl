#include "Time.hpp"

#include <chrono>
#include <ctime>

namespace SSBL {
String GetTimestamp(const String &format) {
    using std::chrono::system_clock;
    const auto currentTime = system_clock::to_time_t(system_clock::now());
    String currentTimeString = std::ctime(&currentTime);

    if (currentTimeString[8] == ' ')
        currentTimeString[8] = '0';

    String timestamp = format;

    timestamp.ReplaceAll("%Y", currentTimeString.GetSubstring(20, 24));
    timestamp.ReplaceAll("%m", currentTimeString.GetSubstring(4, 7));
    timestamp.ReplaceAll("%d", currentTimeString.GetSubstring(8, 10));
    timestamp.ReplaceAll("%D", currentTimeString.GetSubstring(0, 3));
    timestamp.ReplaceAll("%H", currentTimeString.GetSubstring(11, 13));
    timestamp.ReplaceAll("%M", currentTimeString.GetSubstring(14, 16));
    timestamp.ReplaceAll("%S", currentTimeString.GetSubstring(17, 19));

    return timestamp;
}
} // namespace SSBL