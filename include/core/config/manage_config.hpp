/**
 * @file manage_config.hpp
 * @brief 配置文件管理
 * @details 配置文件使用json格式进行存储
 * @author DaneJoe001
 * @date 20250620
 */
#pragma once

#include <unordered_map>
#include <string>

/// @brief 配置项字符串
#define CONFIG_ITEM_STR std::string("config")
/// @brief 默认配置文件路径
#define DEFAULT_CONFIG_PATH std::string("./config/default_config.json")

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
     * @param config_type 配置项类型
     */
    std::unordered_map<std::string, std::string> get_config(const std::string& config_type);
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
    /**
     * @brief 添加配置项
     * @param config_type 配置类型
     * @param config_map 配置项
     */
    void add_config(const std::string& config_type, std::unordered_map<std::string, std::string> config_map);
private:
    /**
     * @brief 解析配置文件
     * @param path 配置文件路径
     */
    void parse_config(const std::string& path);
private:
    /// @brief 配置文件路径
    std::string m_config_path = DEFAULT_CONFIG_PATH;
    /// @brief 配置项
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_config_map;

};