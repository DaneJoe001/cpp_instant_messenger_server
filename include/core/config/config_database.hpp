#pragma once

#include <string>

#include "core/config/manage_config.hpp"
#include "core/database/base_database.hpp"

/**
 * @class ConfigDatabase
 * @brief 数据库配置类
 */
class ConfigDatabase
{
public:
    /**
     * @brief 构造函数
     * @param manage_config 配置管理类
     */
    ConfigDatabase(ManageConfig& manage_config);
    /**
     * @brief 获取数据库配置
     * @return BaseDatabase::DatabaseConfig 数据库配置
     */
    BaseDatabase::DatabaseConfig get_config();
    /**
     * @brief 获取数据库配置字符串
     * @return std::string 数据库配置字符串
     * @note 用于输出调试信息
     */
    std::string get_config_str();
private:
    /// @brief 配置管理类
    ManageConfig& m_manage_config;
};