#include "core/log/manage_log.hpp"

ManageLog::ManageLog()
{
    m_default_log_config.path = "./log/";
    m_default_log_config.name = "default";
    m_default_log_config.is_console_output = true;
    m_default_log_config.is_file_output = true;
    m_default_log_config.console_log_level = BaseLogger::LogLevel::TRACE;
    m_default_log_config.file_log_level = BaseLogger::LogLevel::TRACE;
}

ManageLog& ManageLog::get_instance()
{
    static ManageLog instance;
    return instance;
}

