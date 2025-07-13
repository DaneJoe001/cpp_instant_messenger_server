#pragma once

#include <optional>

#include "data/entity/entity_user.hpp"

class BaseDatabase;

/**
 * @class AccessUser
 * @brief 数据访问层-用户
 */
class AccessUser
{
public:
    /**
     * @brief 构造函数
     * @param database 数据库
     */
    AccessUser(BaseDatabase& database);
    /**
     * @brief 析构函数
     */
    ~AccessUser() = default;
    /**
     *  @brief 初始化用户表
     */
    bool init_user_table();
    /**
     * @brief 添加用户
     * @param user 用户
     */
    bool add_user(const EntityUser& user);
    /**
     * @brief 删除用户
     * @param user_account 用户账号
     */
    bool delete_user(const std::string& user_account);
    /**
     * @brief 获取用户
     * @param user_account 用户账号
     * @return std::optional<EntityUser> 用户
     */
    std::optional<EntityUser> get_user(const std::string& user_account);
    /**
     * @brief 更新用户
     */
    bool update_user(const EntityUser& user);
private:
    /// @brief 数据库
    BaseDatabase& m_database;
};