#include <iostream>

#include "core/log/log_danejoe.hpp"

LogDaneJoe::LogDaneJoe(const LogConfig& config) :BaseLogger(config) {}

bool LogDaneJoe::open()
{
    if (m_log_config.file_path().empty())
    {
        return false;
    }
    if (!m_file_out.is_open())
    {
        m_file_out.open(m_log_config.file_path(), std::ios_base::app);
    }
    return m_file_out.is_open();
}

void LogDaneJoe::output(LogLevel level, const std::string& log_info)
{
    std::string log_level_str;
    switch (level)
    {
    case LogLevel::DEBUG:
        log_level_str = "[DEBUG] ";
        break;
    case LogLevel::INFO:
        log_level_str = "[INFO] ";
        break;
    case LogLevel::WARN:
        log_level_str = "[WARN] ";
        break;
    case LogLevel::ERROR:
        log_level_str = "[ERROR] ";
        break;
    default:
        log_level_str = "[UNKNOWN] ";
    }
    if (m_log_config.is_console_output && level >= m_log_config.console_log_level)
    {
        std::cout << log_level_str << log_info << std::endl;
    }
    if (!m_log_config.file_path().empty() && level >= m_log_config.console_log_level)
    {
        if (!open())
        {
            std::cerr << "[ERROR] Failed to open log file: " << m_log_config.file_path() << std::endl;
            return;
        }
        m_file_out << log_level_str << log_info << std::endl;
    }
}

void LogDaneJoe::debug(const std::string& log_info)
{
    output(LogLevel::DEBUG, log_info);
}

void LogDaneJoe::info(const std::string& log_info)
{
    output(LogLevel::INFO, log_info);
}

void LogDaneJoe::warn(const std::string& log_info)
{
    output(LogLevel::WARN, log_info);
}

void LogDaneJoe::error(const std::string& log_info)
{
    output(LogLevel::ERROR, log_info);
}
void LogDaneJoe::fatal(const std::string& log_info)
{
    output(LogLevel::ERROR, log_info);
    /// @todo 添加异常处理
}

void LogDaneJoe::trace(const std::string& log_info)
{
    output(LogLevel::DEBUG, log_info);
}

