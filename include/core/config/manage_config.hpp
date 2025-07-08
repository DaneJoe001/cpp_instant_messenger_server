#pragma once

#include <unordered_map>
#include <string>

/// @brief 控制是否在配置管理中在控制台输出
/// @note 配置类构建在日志类之前，就不打算引入日志管理了
/// @details 0:TRACE 1:DEBUG 2:INFO 3:WARN 4:ERROR 5:FATAL 6:OFF
#define CONSOLE_OUTPUT_LEVEL 0

/**
 * @file manage_config.hpp
 * @brief 配置文件管理
 * @details 配置文件使用json格式进行存储
 * @author DaneJoe001
 * @date 20250620
 */

 /**
  * @class ManageConfig
  * @brief 配置管理类
  */
class ManageConfig
{
public:
    /**
     * @brief 获取单例对象
     */
    static ManageConfig& get_instance();
    /**
     * @brief 设置配置文件路径
     * @param path 配置文件路径
     */
    void set_config_path(const std::string& path);
    /**
     * @brief 加载配置文件
     */
    void load_config();
    /**
     * @brief 保存配置文件
     */
    void save_config();
    /**
     * @brief 获取配置项
     * @param config_type 配置类型
     * @param config_key 配置项
     */
    std::string get_config(const std::string& config_type, const std::string config_key);
    /**
     * @brief 添加配置项
     * @param config_type 配置类型
     * @param config_key 配置项
     */
    void add_config(const std::string& config_type, const std::string& config_key, const std::string& config_value);
private:
    /**
     * @brief 解析配置文件
     * @param path 配置文件路径
     */
    void parse_config(const std::string& path);
private:
    /// @brief 配置文件路径
    std::string m_config_path = "./config/default.json";
    /// @brief 配置项
    /// @example {database,{host,127.0.0.1},{port,3306}...}
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_config_map;

};