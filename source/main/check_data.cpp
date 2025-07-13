#include <chrono>

#include "main/check_data.hpp"

EntityUser g_user1;
EntityUser g_user2;
EntityUser g_user3;

void init_users()
{
    auto now = std::chrono::system_clock::now();

    // 创建几个用户对象
    g_user1 = EntityUser(
        1,                                // 用户ID
        "user1_account",                  // 用户账号
        "hashed_password_1",              // 密码哈希
        "User One",                       // 昵称
        "http://example.com/avatar1.png", // 头像URL
        "This is user one's signature.",  // 签名
        EntityUser::UserStatus::Online,   // 用户状态
        now,                               // 上次登录时间
        now,                               // 上次登出时间
        "192.168.1.1",                    // 上次登录IP地址
        EntityUser::DeviceType::Desktop,  // 上次登录设备类型
        EntityUser::UserType::Normal,     // 用户类型
        EntityUser::Gender::Male,         // 用户性别
        { "China", "Beijing", "Haidian" },  // 用户位置
        "user1@example.com",               // 用户邮箱
        "12345678901",                     // 用户手机号码
        now,                               // 用户生日
        now                                // 用户注册时间
    );

    g_user2 = EntityUser(
        2,
        "admin_account",
        "hashed_password_2",
        "Admin User",
        "http://example.com/avatar2.png",
        "This is admin user's signature.",
        EntityUser::UserStatus::Offline,
        now,
        now,
        "192.168.1.2",
        EntityUser::DeviceType::Mobile,
        EntityUser::UserType::Admin,
        EntityUser::Gender::Female,
        { "USA", "California", "Los Angeles" },
        "admin@example.com",
        "09876543210",
        now,
        now
    );

    g_user3 = EntityUser(
        3,
        "guest_account",
        "hashed_password_3",
        "Guest User",
        "http://example.com/avatar3.png",
        "This is guest user's signature.",
        EntityUser::UserStatus::Invisible,
        now,
        now,
        "192.168.1.3",
        EntityUser::DeviceType::Tablet,
        EntityUser::UserType::Guest,
        EntityUser::Gender::Other,
        { "Canada", "Ontario", "Toronto" },
        "guest@example.com",
        "11223344556",
        now,
        now
    );
}