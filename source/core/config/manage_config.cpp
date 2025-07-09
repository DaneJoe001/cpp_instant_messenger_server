#include <iostream>
#include <filesystem>

#include "core/config/manage_config.hpp"
#include "core/util/util_json.hpp"

void ManageConfig::set_config_path(const std::string& path)
{
    m_config_path = path;
}
ManageConfig& ManageConfig::get_instance()
{
    static ManageConfig instance;
    return instance;
}

/// @todo 将具体配置项的解析交由对应的配置类
void ManageConfig::load_config()
{
    /// @note 尝试打开文件，当指定配置文件不存在时，创建默认配置文件并返回
    if (m_config_path.empty())
    {
        m_config_path = "./config/default_config.json";
        std::ofstream ofs(m_config_path);
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_INFO
        std::cout << "[INFO] 创建默认配置文件" << std::endl;
#endif
        return;
    }
    if (!std::filesystem::exists(m_config_path))
    {
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_ERROR
        std::cout << "[ERROR] 路径不存在：" << m_config_path << std::endl;
#endif
        return;
    }
    parse_config(m_config_path);

}

void ManageConfig::save_config()
{
    /// @todo 将map以json保存至文件

}

std::unordered_map<std::string, std::string> ManageConfig::get_config(const std::string& config_type)
{
    if (m_config_map.find(config_type) == m_config_map.end())
    {
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_WARN
        std::cout << "[WARN] : Config not found" << std::endl;
#endif
        return std::unordered_map<std::string, std::string>();
    }
    return m_config_map[config_type];
}
std::string ManageConfig::get_config(const std::string& config_type, const std::string config_key)
{
    if (m_config_map.find(config_type) != m_config_map.end())
    {
        return m_config_map[config_type][config_key];
    }
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_WARN
    std::cout << "[WARN] : Config not found" << std::endl;
#endif
    return std::string();
}
void ManageConfig::parse_config(const std::string& path)
{
    if (path.empty())
    {
        return;
    }
    UtilJson json;
    json.load_json_from_path(path);
    nlohmann::json config_json = json.get_value<nlohmann::json>(CONFIG_ITEM_STR, nlohmann::json());
    if (config_json.empty())
    {
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_ERROR
        std::cout << "[ERROR] 配置项不存在" << std::endl;
#endif
        return;
    }
    /// @note 遍历一级配置项
    for (auto& [config_type, config_key] : config_json.items())
    {
        if (config_key.is_object())
        {
            /// @note 遍历二级配置项
            for (auto& [config_key_s, value] : config_key.items())
            {
                if (value.is_string())
                {
                    m_config_map[config_type][config_key_s] = value.get<std::string>();
                }
                else if (value.is_boolean())
                {
                    m_config_map[config_type][config_key_s] = std::to_string(value.get<bool>());
                }
                else if (value.is_number())
                {
                    m_config_map[config_type][config_key_s] = std::to_string(value.get<int>());
                }
                else
                {
                    continue;
                }
            }
        }
        else
        {
            continue;
        }
        /// @todo 考虑处理其它元素
    }
}
void ManageConfig::add_config(const std::string& config_type, const std::string& config_key, const std::string& config_value)
{
    m_config_map[config_type].insert({ config_key, config_value });
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_TRACE
    std::cout << "[TRACE]: " << config_type << " " << config_key << " " << config_value << std::endl;
#endif
}

void ManageConfig::add_config(const std::string& config_type, std::unordered_map<std::string, std::string> config_map)
{
    m_config_map[config_type] = config_map;
}