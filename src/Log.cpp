#include "Log.hpp"
#include "Format.hpp"
#include "Time.hpp"
#include <string>

namespace SSBL {

std::string ToLog(const std::string &string, const Level level, const Config config) {
    std::string log;

    if (static_cast<bool>(config & Config::Timestamp))
        log += WithPadding(GetTimestamp());

    log += WithPadding(LogLevelToString(level));
    log += string;

    if (log.back() != '\n')
        log += '\n';

    return log;
}

std::string LogLevelToString(const Level level) {
    std::string str{};

    switch (level) {
    case Level::Info:
        str = "INF";
        break;
    case Level::Warning:
        str = "WRN";
        break;
    case Level::Error:
        str = "ERR";
        break;
    case Level::Fatal:
        str = "FTL";
        break;
    default:
        str = "UNK";
        break;
    }

    return str;
}
} // namespace SSBL