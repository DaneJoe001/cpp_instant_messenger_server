#pragma once

#include <string>

#include "core/config/manage_config.hpp"
#include "core/log/base_log.hpp"

/**
 * @class ConfigLog
 * @brief 配置日志
 */
class ConfigLog
{
public:
    /**
     * @brief 构造函数
     * @param manage_config 配置管理器
     */
    ConfigLog(ManageConfig& manage_config);
    /**
     * @brief 获取配置
     * @return BaseLogger::LogConfig配置
     */
    BaseLogger::LogConfig get_config();
    /**
     * @brief 获取配置字符串
     * @return 配置字符串
     */
    std::string get_config_str();
private:
    /// @brief 配置管理器
    ManageConfig& m_manage_config;
};