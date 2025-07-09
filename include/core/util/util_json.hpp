#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

/**
 * @class UtilJson
 * @brief json工具类
 */
class UtilJson
{
public:
    /**
     * @brief 默认构造函数
     */
    UtilJson() = default;
    /**
     * @brief 构造函数
     * @param json json对象
     */
    UtilJson(const nlohmann::json& json);
    /**
     * @brief 从路径中加载Json文件
     */
    bool load_json_from_path(const std::string& path);
    /**
     * @brief 从字符串中加载Json文件
     */
    bool load_json_from_string(const std::string& json_string);
    /**
     * @brief 保存Json文件到指定路径
     * @todo 待实现
     */
    bool save_json_to_path(const std::string& path);
    /**
     * @brief 获取Json文件中的值
     * @tparam T 值类型
     * @param key 键
     * @param default_value 默认值
     */
    template<class T>
    T get_value(const std::string& key, const T& default_value)
    {
        try
        {
            if (m_json.contains(key))
            {
                return m_json[key].get<T>();
            }
        }
        catch (const nlohmann::json::exception& e)
        {
#if CONSOLE_OUTPUT_LEVEL <= 3
            std::cout << "[ERROR] 获取键值失败：" << e.what() << std::endl;
#endif
        }
        return default_value;
    }

private:
    /// @brief Json对象
    nlohmann::json m_json;
};