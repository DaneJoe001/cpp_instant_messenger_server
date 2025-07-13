#include <format>
#include <sstream>

#include "core/util/util_time.hpp"
#include "data/entity/entity_user.hpp"

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
    m_email(email), m_phone(phone), m_birthday(age), m_registration_time(registration_time)
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

std::string EntityUser::get_user_info_str()const
{
    std::ostringstream oss;
    oss << "user_id: " << m_user_id
        << ", user_account: " << m_user_account
        << ", nick_name: " << m_nick_name
        << ", phone: " << m_phone
        << ", email: " << m_email
        << ", birthday: " << UtilTime::get_time_str(m_birthday)
        << ", gender: " << static_cast<int>(m_gender) // 将枚举转换为整数
        << ", location: " << m_location.city << ", " << m_location.province << ", " << m_location.country
        << ", signature: " << m_signature
        << ", user_type: " << static_cast<int>(m_user_type) // 将枚举转换为整数
        << ", user_status: " << static_cast<int>(m_user_status) // 将枚举转换为整数
        << ", last_login_time: " << UtilTime::get_time_str(m_last_login_time)
        << ", last_logout_time: " << UtilTime::get_time_str(m_last_logout_time)
        << ", last_ip_address: " << m_last_ip_address
        << ", last_device_type: " << static_cast<int>(m_last_device_type) // 将枚举转换为整数
        << ", avatar_url: " << m_avatar_url
        << ", password_hash: " << m_password_hash;
    return oss.str();
}