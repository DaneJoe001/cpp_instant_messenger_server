#include "core/database/base_database.hpp"


template<class T>
BaseStatement& BaseStatement::arg(const T& value)
{
    size_t pos = this->find("?");
    if (pos != std::string::npos)
    {
        this->replace(pos, 1, std::to_string(value));
    }
    return *this;
}

BaseDatabase::BaseDatabase(std::shared_ptr<BaseLogger> logger) : m_logger(logger) {}

void BaseDatabase::set_path(const std::string& path)
{
    if (path.empty())
    {
        m_logger->warn("path is empty");
    }
    m_config.path = path;
}

void BaseDatabase::set_user_name(const std::string& user_name)
{
    if (user_name.empty())
    {
        m_logger->warn("user_name is empty");
    }
    m_config.user_name = user_name;
}

void BaseDatabase::set_user_password(const std::string& user_password)
{
    if (user_password.empty())
    {
        m_logger->warn("user_password is empty");
    }
    m_config.user_password = user_password;
}

void BaseDatabase::set_database_name(const std::string& database_name)
{
    if (database_name.empty())
    {
        m_logger->warn("database_name is empty");
    }
    m_config.database_name = database_name;
}

void BaseDatabase::set_config(const DatabaseConfig& config)
{
    m_config = config;
}