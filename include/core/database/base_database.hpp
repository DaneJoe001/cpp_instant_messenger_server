#pragma once

#include <string>
#include <cstdint>
#include <vector>

/// @todo 使用format

/// 设计一个arg函数拓展，填充位置只要查询当前位置最小的地方即可，不对，不能用arg的方式，还是得用多参的方式传递

/**
 * @brief Statement 类用于表示数据库查询语句。
 * 该类继承自 std::string，并提供了参数化查询的功能。
 * 可以通过 arg 方法添加参数到查询语句中。
 * @note 该类是一个抽象基类，必须实现 replace 方法来替换占位符。
 * @todo 后面再考虑完善实现以适应不同的数据库
 */
class BaseStatement :public std::string
{
public:
    /**
     * @brief 添加参数到查询语句中。
     * @param value 参数值。
     */
    template<class T>
    BaseStatement& arg(const T& value);
    /**
     * @brief 替换占位符。
     * @param placeholder 占位符。
     * @param value 替换的值。
     */
    virtual void replace(const std::string& placeholder, const std::string& value) = 0;
};

/**
 * @class BaseDatabase 数据库抽象类
 * @brief 数据库抽象类，定义了数据库操作的接口。
 */
class BaseDatabase
{
public:
    /**
     * @brief 连接到数据库。
     * @note 该方法必须被实现。
     */
    virtual void connect() = 0;
    /**
     * @brief 执行操作。
     * @param statement 查询语句。
     */
    virtual void execute(const std::string& statement) = 0;
    /**
     * @brief 查询操作。
     * @param statement 查询语句。
     */
    virtual std::vector<std::vector<std::string>> query(const std::string& statement) = 0;
    /**
     * @brief 获取错误信息。
     */
    virtual std::string error_message() = 0;
    /**
     * @brief 获取错误码。
     */
    virtual std::string error_code() = 0;
    /**
     * @brief 设置数据库路径。
     * @param path 数据库路径。
     */
    void set_path(const std::string& path);
    /**
     * @brief 设置用户名。
     * @param user_name 用户名。
     */
    void set_user_name(const std::string& user_name);
    /**
     * @brief 设置密码。
     * @param user_password 密码。
     */
    void set_user_password(const std::string& user_password);
    /**
     * @brief 设置数据库名称。
     * @param database_name 数据库名称。
     */
    void set_database_name(const std::string& database_name);

protected:
    /// @brief 错误信息
    std::string m_error_message;
    /// @brief 错误码
    std::string m_error_code;
    /// @brief 数据库路径
    std::string m_path;
    /// @brief 用户名
    std::string m_user_name;
    /// @brief 密码
    std::string m_user_password;
    /// @brief 数据库名称
    std::string m_database_name;
};