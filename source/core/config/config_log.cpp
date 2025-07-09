#include <string>

#include "core/config/manage_config.hpp"
#include "core/log/base_log.hpp"
#include "core/config/config_log.hpp"
#include "core/util/util_print.hpp"

ConfigLog::ConfigLog(ManageConfig& manage_config) :m_manage_config(manage_config) {}
BaseLogger::LogConfig ConfigLog::get_config()
{
    BaseLogger::LogConfig log_config;
    log_config.path = m_manage_config.get_config(LOG_ITEM_STR, LOG_PATH_STR);
    if (log_config.path.empty())
    {
        log_config.path = DEFAULT_LOG_PATH;
    }
    log_config.name = m_manage_config.get_config(LOG_ITEM_STR, LOG_NAME_STR);
    if (log_config.name.empty())
    {
        log_config.name = DEFAULT_LOG_NAME;
    }
    /// @todo 考虑配置获取使用模板输出为指定类型(bool,int,string)
    log_config.is_console_output = m_manage_config.get_config(LOG_ITEM_STR, LOG_IS_CONSOLE_OUTPUT_STR) == DEFAULT_LOG_IS_CONSOLE_OUTPUT;
    log_config.is_file_output = m_manage_config.get_config(LOG_ITEM_STR, LOG_IS_FILE_OUTPUT_STR) == DEFAULT_LOG_IS_FILE_OUTPUT;
    /// @todo 级别配置表示方式采用数字和大写宏两种
    log_config.console_log_level = BaseLogger::LogLevel(std::atoi(m_manage_config.get_config(LOG_ITEM_STR, LOG_CONSOLE_LOG_LEVEL_STR).c_str()));
    log_config.file_log_level = BaseLogger::LogLevel(std::atoi(m_manage_config.get_config(LOG_ITEM_STR, LOG_FILE_LOG_LEVEL_STR).c_str()));

    return log_config;
}

std::string ConfigLog::get_config_str()
{
    /// @todo 调整输出格式
    return "[LOG_CONFIG]\n" + UtilPrint::get_str(m_manage_config.get_config(LOG_ITEM_STR));
}