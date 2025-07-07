#pragma once

#include <memory>

#include <SQLiteCpp/SQLiteCpp.h>

#include <core/database/base_database.hpp>

/**
 * @class DatabaseSQLite
 * @brief SQLite数据库
 */
class DatabaseSQLite : public BaseDatabase
{
public:
    /**
     * @brief 构造函数
     */
    DatabaseSQLite();
    /**
     * @brief 析构函数
     */
    ~DatabaseSQLite();
    /**
     * @brief 连接数据库
     */
    virtual void connect() override;
    /**
     * @brief 执行SQL语句
     */
    virtual void execute(const std::string& statement) override;
    /**
     * @brief 查询SQL语句
     */
    virtual std::vector<std::vector<std::string>> query(const std::string& statement) override;
    /**
     * @brief 获取错误信息
     */
    virtual std::string error_message() override;
    /**
     * @brief 获取错误码
     */
    virtual std::string error_code() override;
private:
    /// @brief 数据库连接
    std::unique_ptr<SQLite::Database> m_database;
};