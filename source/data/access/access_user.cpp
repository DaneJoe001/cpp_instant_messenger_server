#include <format>
#include <regex>

#include "core/database/base_database.hpp"
#include "data/access/access_user.hpp"

AccessUser::AccessUser(BaseDatabase& database) :m_database(database) {}

bool AccessUser::init_user_table()
{
    std::string statement = std::format(
        "CREATE TABLE IF NOT EXISTS users ("
        "user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user_account TEXT UNIQUE NOT NULL, "
        "password_hash TEXT NOT NULL, "
        "nick_name TEXT NOT NULL, "
        "avatar_url TEXT, "
        "signature TEXT, "
        "user_status INTEGER NOT NULL, "  // 使用 INTEGER 来存储枚举值
        "user_type INTEGER NOT NULL, "      // 使用 INTEGER 来存储枚举值
        "last_device_type INTEGER NOT NULL, " // 使用 INTEGER 来存储枚举值
        "last_ip_address TEXT NOT NULL, "
        "last_login_time INTEGER, "          // 存储为时间戳（INTEGER）
        "last_logout_time INTEGER, "         // 存储为时间戳（INTEGER）
        "email TEXT UNIQUE, "                // 用户邮箱
        "phone TEXT UNIQUE, "                // 用户手机号码
        "birthday INTEGER, "                 // 存储为时间戳（INTEGER）
        "registration_time INTEGER "          // 存储为时间戳（INTEGER）
        ");"
    );
    return m_database.execute(statement);
}

bool AccessUser::add_user(const EntityUser& user)
{
    /// @todo 检查用户是否已存在
    std::string statement = std::format(
        "INSERT INTO users ("
        "password_hash, "
        "nick_name, "
        "avatar_url, "
        "signature, "
        "user_status, "
        "user_type, "
        "last_device_type, "
        "last_ip_address, "
        "last_login_time, "
        "last_logout_time, "
        "email, "
        "phone, "
        "birthday, "
        "registration_time, "
        "user_account"
        ") VALUES ("
        "'{}', "
        "'{}', "
        "'{}', "
        "'{}', "
        "{}, "
        "{}, "
        "{}, "
        "'{}', "
        "{}, "  // last_login_time
        "{}, "  // last_logout_time
        "'{}', "
        "'{}', "
        "{}, "  // birthday
        "{}, "  // registration_time
        "'{}'"
        ");",
        user.m_password_hash,
        user.m_nick_name,
        user.m_avatar_url,
        std::regex_replace(user.m_signature, std::regex("'"), "''"),  // 转义单引号
        static_cast<int>(user.m_user_status),
        static_cast<int>(user.m_user_type),
        static_cast<int>(user.m_last_device_type),
        user.m_last_ip_address,
        std::chrono::system_clock::to_time_t(user.m_last_login_time),  // 转换为时间戳
        std::chrono::system_clock::to_time_t(user.m_last_logout_time), // 转换为时间戳
        user.m_email,
        user.m_phone,
        std::chrono::system_clock::to_time_t(user.m_birthday),             // 转换为时间戳
        std::chrono::system_clock::to_time_t(user.m_registration_time), // 转换为时间戳
        user.m_user_account
    );

    return m_database.execute(statement);
};

bool AccessUser::delete_user(const std::string& user_account)
{
    std::string statement = std::format("DELETE FROM users WHERE user_account = '{}';", user_account);
    return m_database.execute(statement);
}

std::optional<EntityUser> AccessUser::get_user(const std::string& user_account)
{
    std::string statement = std::format("SELECT * FROM users WHERE user_account = '{}';", user_account);
    std::vector<std::vector<std::string>> result = m_database.query(statement);
    if (result.size() == 0)
    {
        return std::nullopt;
    }
    EntityUser user;
    /// @todo 使用正则表达式检查数据
    user.m_user_id = std::stoi(result[0][0]);
    user.m_user_account = result[0][1];
    user.m_password_hash = result[0][2];
    user.m_nick_name = result[0][3];
    user.m_signature = result[0][4];
    user.m_avatar_url = result[0][5];
    user.m_user_type = static_cast<EntityUser::UserType>(std::stoi(result[0][6]));
    user.m_user_status = static_cast<EntityUser::UserStatus>(std::stoi(result[0][7]));
    user.m_last_device_type = static_cast<EntityUser::DeviceType>(std::stoi(result[0][8]));
    user.m_last_ip_address = result[0][9];
    user.m_last_login_time = std::chrono::system_clock::from_time_t(std::stol(result[0][10]));
    user.m_last_logout_time = std::chrono::system_clock::from_time_t(std::stol(result[0][11]));
    return user;
}

bool AccessUser::update_user(const EntityUser& user)
{
    std::string statement = std::format(
        "UPDATE users SET "
        "password_hash = '{}', "
        "nick_name = '{}', "
        "avatar_url = '{}', "
        "signature = '{}', "
        "user_status = {}, "
        "user_type = {}, "
        "last_device_type = {}, "
        "last_ip_address = '{}', "
        "last_login_time = {}, "
        "last_logout_time = {}, "
        "email = '{}', "
        "phone = '{}', "
        "birthday = {}, "
        "registration_time = {} "
        "WHERE user_account = '{}';",
        user.m_password_hash,
        user.m_nick_name,
        user.m_avatar_url,
        std::regex_replace(user.m_signature, std::regex("'"), "''"),  // 转义单引号
        static_cast<int>(user.m_user_status),
        static_cast<int>(user.m_user_type),
        static_cast<int>(user.m_last_device_type),
        user.m_last_ip_address,
        std::chrono::system_clock::to_time_t(user.m_last_login_time),  // 转换为时间戳
        std::chrono::system_clock::to_time_t(user.m_last_logout_time), // 转换为时间戳
        user.m_email,
        user.m_phone,
        std::chrono::system_clock::to_time_t(user.m_birthday),             // 转换为时间戳
        std::chrono::system_clock::to_time_t(user.m_registration_time), // 转换为时间戳
        user.m_user_account
    );

    return m_database.execute(statement);
}