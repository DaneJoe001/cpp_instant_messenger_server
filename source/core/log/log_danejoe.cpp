#include <iostream>
// #include <format>

#include "core/log/log_danejoe.hpp"
#include "core/util/util_time.hpp"
#include "core/util/util_print.hpp"

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
    // std::string log_level_str;
    UtilPrint::LogLevel log_level;
    switch (level)
    {
    case LogLevel::TRACE:log_level = UtilPrint::LogLevel::TRACE;break;
    case LogLevel::DEBUG:log_level = UtilPrint::LogLevel::DEBUG;break;
    case LogLevel::INFO:log_level = UtilPrint::LogLevel::INFO;break;
    case LogLevel::WARN:log_level = UtilPrint::LogLevel::WARN;break;
    case LogLevel::ERROR:log_level = UtilPrint::LogLevel::ERROR;break;
    case LogLevel::FATAL:log_level = UtilPrint::LogLevel::FATAL;break;
    default:log_level = UtilPrint::LogLevel::TRACE;break;
    }
    /// @brief UtilPrint的日志格式构建设置
    UtilPrint::OutputSetting output_setting = get_output_setting();
    /// @brief 获取日志字符串
    std::string log_str = UtilPrint::get_log_str(log_level, log_info, output_setting);
    /// @brief 控制台输出日志
    if (m_log_config.is_console_output && level >= m_log_config.console_log_level)
    {
        UtilPrint::print(log_str);
    }
    if (!m_log_config.file_path().empty() && level >= m_log_config.console_log_level)
    {
        if (!open())
        {
            UtilPrint::print(UtilPrint::LogLevel::ERROR, "打开日志文件失败：" + m_log_config.file_path(), output_setting);
        }
        {
            std::lock_guard<std::mutex>lock(m_file_mutex);
            m_file_out << log_str << std::endl;
        }
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

