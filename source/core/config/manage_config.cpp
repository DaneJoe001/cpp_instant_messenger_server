#include <iostream>

#include "core/config/manage_config.hpp"

void ManageConfig::set_config_path(const std::string& path)
{
    m_config_path = path;
}
ManageConfig& ManageConfig::get_instance()
{
    static ManageConfig instance;
    return instance;
}
void ManageConfig::load_config()
{
    /// @todo 尝试打开文件，当指定配置文件不存在时，创建默认配置文件

}
void ManageConfig::save_config()
{
    /// @todo 将map以json保存至文件

}
std::string ManageConfig::get_config(const std::string& config_type, const std::string config_key)
{
    if (m_config_map.find(config_type) != m_config_map.end())
    {
        return m_config_map[config_type][config_key];
    }
#if CONSOLE_OUTPUT_LEVEL <= 3
    std::cout << "[WARN] : Config not found" << std::endl;
#endif
    return std::string("");
}
void ManageConfig::parse_config(const std::string& path)
{

}
void ManageConfig::add_config(const std::string& config_type, const std::string& config_key, const std::string& config_value)
{
    m_config_map[config_type].insert({ config_key, config_value });
#if CONSOLE_OUTPUT_LEVEL == 1
    std::cout << "[TRACE]: " << config_type << " " << config_key << " " << config_value << std::endl;
#endif
}