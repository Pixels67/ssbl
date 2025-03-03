#include "Time.hpp"

#include <chrono>
#include <ctime>

namespace SSBL {
std::string GetTimestamp() {
    using std::chrono::system_clock;

    const auto currentTime = system_clock::to_time_t(system_clock::now());

    std::string currentTimeString = ctime(&currentTime);
    currentTimeString.pop_back();

    return currentTimeString;
}
} // namespace SSBL