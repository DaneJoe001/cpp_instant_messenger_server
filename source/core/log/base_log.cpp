#include "core/log/base_log.hpp"
#include "core/util/util_time.hpp"

BaseLogger::BaseLogger(const BaseLogger::LogConfig& config) :m_log_config(config) {}

void BaseLogger::set_config(const BaseLogger::LogConfig& config)
{
    m_log_config = config;
}