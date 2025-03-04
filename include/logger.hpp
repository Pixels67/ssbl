#pragma once

#include "Format.hpp"
#include "Log.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace SSBL {
class Logger {
public:
    Logger &Log(Level level = Level::Info);
    Logger &LogToFile(const std::string &filePath, Level level = Level::Info);

    template<typename T>
    Logger &operator<<(const T &stream) {
        if (!IsLevelIncluded(m_level))
            return *this;

        m_stream.str(Format(m_stream.str(), GenericToString(stream), insertCount));
        insertCount++;

        if (Contains(GenericToString(stream), "\n")) {
            Send(m_stream.str());
            Flush();
        }

        return *this;
    }

    void SetOutStream(std::ostream *messageOutStream, std::ostream *errorOutStream);
    void SetConfig(const Config &config);
    void SetLevelMask(Level level);
    bool IsLevelIncluded(Level level) const;

private:
    std::ostream *m_msgOutStream = &std::cout;
    std::ostream *m_errOutStream = &std::cerr;
    std::optional<std::ofstream> m_fileOutStream;

    std::ostringstream m_stream;
    size_t insertCount = 0;

    Config m_config = Config::Timestamp;
    Level m_levelMask = Level::All;
    Level m_level = Level::Info;

    void Send(const std::string &string);
    void Flush();

    void SetColor();
    void ResetColor() const;

#if _WIN32
    int GetColor() const;
#else
    std::string GetColor() const;
#endif
};
} // namespace SSBL