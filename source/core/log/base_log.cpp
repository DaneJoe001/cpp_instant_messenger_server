#include "core/log/base_log.hpp"

BaseLogger::BaseLogger(const BaseLogger::LogConfig& config) :m_log_config(config) {}

void BaseLogger::set_config(const BaseLogger::LogConfig& config)
{
    m_log_config = config;
}