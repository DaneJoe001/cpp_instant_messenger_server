#pragma once

#include <string>

#include "core/config/manage_config.hpp"
#include "core/database/base_database.hpp"

/// @todo 调整配置结构
/// @brief 数据库配置项名称字符串
#define DATABASE_ITEM_STR std::string("sqlite")
/// @brief 数据库名称字符串
#define DATABASE_NAME_STR std::string("database_name")
/// @brief 数据库路径字符串
#define DATABASE_PATH_STR std::string("path")
/// @brief 数据库用户名字符串
#define DATABASE_USER_NAME_STR std::string("user_name")
#define DATABASE_USER_PASSWORD_STR std::string("user_password")

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