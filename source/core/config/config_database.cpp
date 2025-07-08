#include "core/config/config_database.hpp"

ConfigDatabase::ConfigDatabase(ManageConfig& manage_config) :m_manage_config(manage_config) {}

BaseDatabase::DatabaseConfig ConfigDatabase::get_config()
{
    BaseDatabase::DatabaseConfig database_config;
    database_config.database_name = m_manage_config.get_config("DATABASE", "database_name");
    database_config.path = m_manage_config.get_config("DATABASE", "path");
    database_config.user_name = m_manage_config.get_config("DATABASE", "user_name");
    database_config.user_password = m_manage_config.get_config("DATABASE", "user_password");
    return database_config;
}
std::string ConfigDatabase::get_config_str()
{
    return "[INFO] " + m_manage_config.get_config("DATABASE", "database_name") + " " +
        m_manage_config.get_config("DATABASE", "path") + " " +
        m_manage_config.get_config("DATABASE", "user_name") + " " +
        m_manage_config.get_config("DATABASE", "user_password");
}