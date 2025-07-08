#include <string>

#include "core/config/manage_config.hpp"
#include "core/log/base_log.hpp"
#include "core/config/config_log.hpp"

ConfigLog::ConfigLog(ManageConfig& manage_config) :m_manage_config(manage_config) {}
BaseLogger::LogConfig ConfigLog::get_config()
{
    BaseLogger::LogConfig log_config;
    log_config.path = m_manage_config.get_config("LOG", "path");
    if (log_config.path.empty())
    {
        log_config.path = "./log/";
    }
    log_config.name = m_manage_config.get_config("LOG", "name");
    if (log_config.name.empty())
    {
        log_config.name = "default";
    }
    /// @todo 考虑配置获取使用模板输出为指定类型(bool,int,string)
    log_config.is_console_output = m_manage_config.get_config("LOG", "is_console_output") == "1";
    log_config.is_file_output = m_manage_config.get_config("LOG", "is_file_output") == "1";
    /// @todo 级别配置表示方式采用数字和大写宏两种
    log_config.console_log_level = BaseLogger::LogLevel(std::atoi(m_manage_config.get_config("LOG", "console_log_level").c_str()));
    log_config.file_log_level = BaseLogger::LogLevel(std::atoi(m_manage_config.get_config("LOG", "file_log_level").c_str()));

    return log_config;
};

std::string ConfigLog::get_config_str()
{
    return "[LOG_CONFIG] " + m_manage_config.get_config("LOG", "path") + m_manage_config.get_config("LOG", "name") + m_manage_config.get_config("LOG", "is_console_output") + m_manage_config.get_config("LOG", "is_file_output") + m_manage_config.get_config("LOG", "console_log_level") + m_manage_config.get_config("LOG", "file_log_level");
}