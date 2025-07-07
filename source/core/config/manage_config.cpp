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
    if (m_config_path.empty())
    {
        //TODO:log failed
        return;
    }
}
void ManageConfig::save_config()
{

}
std::string ManageConfig::get_config(const std::string& config_type, const std::string config_key)
{

}
void ManageConfig::parse_config(const std::string& path)
{

}
void ManageConfig::add_config(const std::string& config_type, const std::string& config_key, const std::string& config_value)
{

}