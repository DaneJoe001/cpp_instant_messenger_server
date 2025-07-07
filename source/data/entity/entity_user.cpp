#include <data/entity/entity_user.hpp>

EntityUser::EntityUser(int id, const std::string& account, const std::string& password_hash,
    const std::string& nick_name, const std::string& avatar_url, const std::string& signature,
    UserStatus status, const std::chrono::system_clock::time_point& last_login_time,
    const std::chrono::system_clock::time_point& last_logout_time, const std::string& last_ip_address,
    DeviceType device_type, UserType user_type, Gender gender, const Location& location,
    const std::string& email, const std::string& phone,
    const std::chrono::system_clock::time_point& age,
    const std::chrono::system_clock::time_point& registration_time) : m_user_id(id), m_user_account(account),
    m_password_hash(password_hash), m_nick_name(nick_name), m_avatar_url(avatar_url),
    m_signature(signature), m_user_status(status), m_last_login_time(last_login_time),
    m_last_logout_time(last_logout_time), m_last_ip_address(last_ip_address),
    m_last_device_type(device_type), m_user_type(user_type), m_gender(gender), m_location(location),
    m_email(email), m_phone(phone), m_age(age), m_registration_time(registration_time)
{

}

void EntityUser::set_user_account(const std::string& account)
{
    m_user_account = account;
}

void EntityUser::set_password_hash(const std::string& password_hash)
{
    m_password_hash = password_hash;
}
void EntityUser::set_nick_name(const std::string& nick_name)
{
    m_nick_name = nick_name;
}
void EntityUser::set_avatar_url(const std::string& avatar_url)
{
    m_avatar_url = avatar_url;
}
void EntityUser::set_signature(const std::string& signature)
{
    m_signature = signature;
}
void EntityUser::set_user_status(UserStatus status)
{
    m_user_status = status;
}
void EntityUser::set_last_login_time(const std::chrono::system_clock::time_point& last_login_time)
{
    m_last_login_time = last_login_time;
}
void EntityUser::set_last_logout_time(const std::chrono::system_clock::time_point& last_logout_time)
{
    m_last_logout_time = last_logout_time;
}
void EntityUser::set_last_ip_address(const std::string& last_ip_address)
{
    m_last_ip_address = last_ip_address;
}
void EntityUser::set_last_device_type(DeviceType device_type)
{
    m_last_device_type = device_type;
}
void EntityUser::set_user_type(UserType user_type)
{
    m_user_type = user_type;
}