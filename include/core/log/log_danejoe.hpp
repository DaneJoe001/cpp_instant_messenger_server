#pragma once

#include <fstream>

#include "core/log/base_log.hpp"

/// @todo 引入线程

class LogDaneJoe : public BaseLogger
{
public:
    LogDaneJoe() = default;
    LogDaneJoe(const LogConfig& config);
    bool open();
    void output(LogLevel level, const std::string& log_info);
    void debug(const std::string& log_info) override;
    void error(const std::string& log_info) override;
    void fatal(const std::string& log_info) override;
    void warn(const std::string& log_info) override;
    void info(const std::string& log_info) override;
    void trace(const std::string& log_info) override;
private:
    std::ofstream m_file_out;
};