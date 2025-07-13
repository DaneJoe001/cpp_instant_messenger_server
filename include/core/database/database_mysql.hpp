#pragma once

#include <memory>
#include <iostream>

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include <core/database/base_database.hpp>

/**
 * @class DatabaseMySQL
 * @brief 数据库MySQL
 */
class DatabaseMySQL : public BaseDatabase {
public:
    /**
     * @brief 构造函数
     */
    DatabaseMySQL(std::shared_ptr<BaseLogger> logger);
    /**
     * @brief 析构函数
     */
    ~DatabaseMySQL();
    /**
     * @brief 连接数据库
     */
    virtual bool connect() override;
    /**
     * @brief 执行SQL语句
     */
    virtual bool execute(const std::string& statement) override;
    /**
     * @brief 查询数据库
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
    /// @brief 数据库驱动
    std::unique_ptr<sql::mysql::MySQL_Driver> m_driver;
    /// @brief 数据库连接
    std::unique_ptr<sql::Connection> m_connection;
};