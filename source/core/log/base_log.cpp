#include "core/log/base_log.hpp"
#include "core/util/util_time.hpp"

BaseLogger::BaseLogger(const BaseLogger::LogConfig& config) :m_log_config(config) {}

void BaseLogger::set_config(const BaseLogger::LogConfig& config)
{
    m_log_config = config;
}

void BaseLogger::set_level_is_visible(bool statu)
{
    m_is_time_visible = statu;
}

void BaseLogger::set_time_is_visible(bool statu)
{
    m_is_level_visible = statu;
}

void BaseLogger::set_file_name_is_visible(bool statu)
{
    m_is_file_name_visible = statu;
}
void BaseLogger::set_line_is_visible(bool statu)
{
    m_is_line_visible = statu;
}
void BaseLogger::set_function_is_visible(bool statu)
{
    m_is_function_visible = statu;
}

UtilPrint::OutputSetting BaseLogger::get_output_setting()
{
    UtilPrint::OutputSetting output_setting;
    output_setting.is_file_name_visible = m_is_file_name_visible;
    output_setting.is_function_visible = m_is_function_visible;
    output_setting.is_level_visible = m_is_level_visible;
    output_setting.is_line_visible = m_is_line_visible;
    output_setting.is_time_visible = m_is_time_visible;
    return output_setting;
}