#include <core/database/base_database.hpp>


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

void BaseDatabase::set_path(const std::string& path)
{
    m_path = path;
}

void BaseDatabase::set_user_name(const std::string& user_name)
{
    m_user_name = user_name;
}

void BaseDatabase::set_user_password(const std::string& user_password)
{
    m_user_password = user_password;
}

void BaseDatabase::set_database_name(const std::string& database_name)
{
    m_database_name = database_name;
}