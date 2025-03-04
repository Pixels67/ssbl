#pragma once

#include "Time.hpp"
#include <string>

namespace SSBL {
enum class Level : unsigned {
    None    = 0b0000,
    Info    = 0b0001,
    Warning = 0b0010,
    Error   = 0b0100,
    Fatal   = 0b1000,
    All     = 0b1111
};

constexpr Level operator|(Level a, Level b) {
    return static_cast<Level>(static_cast<char>(a) | static_cast<char>(b));
}

constexpr Level operator&(Level a, Level b) {
    return static_cast<Level>(static_cast<char>(a) & static_cast<char>(b));
}

constexpr Level operator~(Level level) {
    return static_cast<Level>(~static_cast<char>(level));
}

enum class Config : unsigned {
    None      = 0b00,
    Color     = 0b01,
    Timestamp = 0b10,
    All       = 0b11
};

constexpr Config operator|(Config a, Config b) {
    return static_cast<Config>(static_cast<char>(a) | static_cast<char>(b));
}

constexpr Config operator&(Config a, Config b) {
    return static_cast<Config>(static_cast<char>(a) & static_cast<char>(b));
}

constexpr Config operator~(Config level) {
    return static_cast<Config>(~static_cast<char>(level));
}

std::string ToLog(const std::string &string, Level level, Config config, const std::string &timestampFormat = DEFAULT_FORMAT);
std::string LogLevelToString(Level level);
} // namespace SSBL