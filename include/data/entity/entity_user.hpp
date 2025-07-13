#pragma once

#include <string>
#include <chrono>

/**
 * @class EntityUser
 * @brief 用户实体类
 */
class EntityUser
{
public:
    /**
     * @class UserType
     * @brief 用户类型枚举类
     */
    enum class UserType
    {
        /// @brief 普通用户
        Normal = 0,
        /// @brief 管理员
        Admin = 1,
        /// @brief 游客
        Guest = 2
    };
    /**
     * @class UserStatus
     * @brief 用户状态枚举类
     */
    enum class UserStatus
    {
        /// @brief 离线
        Offline = 0,
        /// @brief 在线
        Online = 1,
        /// @brief 忙碌
        Busy = 2,
        /// @brief 隐身
        Invisible = 3
    };
    /**
     * @class DeviceType
     * @brief 设备类型枚举类
     */
    enum class DeviceType
    {
        /// @brief 桌面
        Desktop = 0,
        /// @brief 手机
        Mobile = 1,
        /// @brief 平板
        Tablet = 2,
        /// @brief 嵌入式设备
        embedded = 3
    };
    /**
     * @class Gender
     * @brief 性别枚举类
     */
    enum class Gender
    {
        /// @brief 男性
        Male = 0,
        /// @brief 女性
        Female = 1,
        /// @brief 其他
        Other = 2 // Other
    };
    /**
     * @struct Location
     * @brief 位置结构体
     */
    struct Location
    {
        /// @brief 国家
        std::string country;
        /// @brief 省份
        std::string province;
        /// @brief 城市
        std::string city;
    };
public:
    /**
     *  @brief 默认构造函数
     */
    EntityUser() = default;
    /**
     * @brief 构造函数
     */
    EntityUser(int id, const std::string& account, const std::string& password_hash,
        const std::string& nick_name, const std::string& avatar_url, const std::string& signature,
        UserStatus status, const std::chrono::system_clock::time_point& last_login_time,
        const std::chrono::system_clock::time_point& last_logout_time, const std::string& last_ip_address,
        DeviceType device_type, UserType user_type, Gender gender, const Location& location,
        const std::string& email, const std::string& phone,
        const std::chrono::system_clock::time_point& age,
        const std::chrono::system_clock::time_point& registration_time);
    /**
     * @brief 设置用户账号
     * @param account 用户账号
     */
    void set_user_account(const std::string& account);
    /**
     * @brief 获取用户账号
     * @param password_hash 用户密码哈希
     */
    void set_password_hash(const std::string& password_hash);
    /**
     * @brief 获取用户昵称
     * @param nick_name 用户昵称
     */
    void set_nick_name(const std::string& nick_name);
    /**
     * @brief 获取用户头像URL
     * @param avatar_url 用户头像URL
     */
    void set_avatar_url(const std::string& avatar_url);
    /**
     * @brief 获取用户签名
     * @param signature 用户签名
     */
    void set_signature(const std::string& signature);
    /**
     * @brief 获取用户状态
     * @param status 用户状态
     */
    void set_user_status(UserStatus status);
    /**
     * @brief 获取用户上次登录时间
     * @param last_login_time 用户上次登录时间
     */
    void set_last_login_time(const std::chrono::system_clock::time_point& last_login_time);
    /**
     * @brief 获取用户上次登出时间
     * @param last_logout_time 用户上次登出时间
     */
    void set_last_logout_time(const std::chrono::system_clock::time_point& last_logout_time);
    /**
     * @brief 获取用户上次登录IP地址
     * @param last_ip_address 用户上次登录IP地址
     */
    void set_last_ip_address(const std::string& last_ip_address);
    /**
     * @brief 获取用户上次登录设备类型
     * @param device_type 用户上次登录设备类型
     */
    void set_last_device_type(DeviceType device_type);
    /**
     * @brief 获取用户类型
     * @param user_type 用户类型
     */
    void set_user_type(UserType user_type);
    /**
     *  @brief 获取用户信息字符串
     */
    std::string get_user_info_str()const;
public:
    /// @brief  用户ID(数据库内自增)
    int m_user_id = -1;
    /// @brief 用户账号
    std::string m_user_account = "000000";
    /// @brief 用户密码哈希
    std::string m_password_hash = "000000";
    /// @brief 用户昵称
    std::string m_nick_name = "default";
    /// @brief 用户头像URL
    std::string m_avatar_url = "default";
    /// @brief 用户签名
    std::string m_signature = "default";
    /// @brief 用户状态
    UserStatus m_user_status = UserStatus::Offline;
    /// @brief 上次登录时间
    std::chrono::system_clock::time_point m_last_login_time;
    /// @brief 上次登出时间
    std::chrono::system_clock::time_point m_last_logout_time;
    /// @brief 上次登录IP地址
    std::string m_last_ip_address = "0.0.0.0";
    /// @brief 上次登录设备类型
    DeviceType m_last_device_type;
    /// @brief 用户类型
    UserType m_user_type = UserType::Normal;
    /// @brief 用户性别
    Gender m_gender = Gender::Other;
    /// @brief 用户位置
    Location m_location;
    /// @brief 用户邮箱
    std::string m_email;
    /// @brief 用户手机号码
    std::string m_phone;
    /// @brief 用户生日
    std::chrono::system_clock::time_point m_birthday;
    /// @brief 用户注册时间
    std::chrono::system_clock::time_point m_registration_time;
};