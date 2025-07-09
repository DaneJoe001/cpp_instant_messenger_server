#include "core/config/config_database.hpp"

#include "core/util/util_print.hpp"

ConfigDatabase::ConfigDatabase(ManageConfig& manage_config) :m_manage_config(manage_config) {}

BaseDatabase::DatabaseConfig ConfigDatabase::get_config()
{
    BaseDatabase::DatabaseConfig database_config;
    database_config.database_name = m_manage_config.get_config(DATABASE_ITEM_STR, DATABASE_NAME_STR);
    database_config.path = m_manage_config.get_config(DATABASE_ITEM_STR, DATABASE_PATH_STR);
    database_config.user_name = m_manage_config.get_config(DATABASE_ITEM_STR, DATABASE_USER_NAME_STR);
    database_config.user_password = m_manage_config.get_config(DATABASE_ITEM_STR, DATABASE_USER_PASSWORD_STR);
    return database_config;
}
std::string ConfigDatabase::get_config_str()
{
    return "[DATABASE_CONFIG]\n" + UtilPrint::get_str(m_manage_config.get_config(DATABASE_ITEM_STR));
}