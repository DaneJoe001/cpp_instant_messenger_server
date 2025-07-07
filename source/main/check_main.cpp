#include <main/check_main.hpp>
#include <core/database/database_sqlite.hpp>
#include <core/database/database_mysql.hpp>
#include <iostream>

void check_sqlite()
{
    try {
        std::cout << "测试 SQLite 数据库..." << std::endl;
        DatabaseSQLite sqlite;
        sqlite.set_path("test.db");
        sqlite.connect();
        sqlite.execute("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, account TEXT, password_hash TEXT, nick_name TEXT, signature TEXT, avatar_url TEXT, user_type INTEGER, user_status INTEGER, last_device_type INTEGER, last_ip_address TEXT, last_login_time TEXT, last_logout_time TEXT)");
        std::cout << "SQLite 测试完成" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "SQLite 测试异常: " << e.what() << std::endl;
    }
}

void check_mysql()
{
    try {
        std::cout << "测试 MySQL 数据库..." << std::endl;
        DatabaseMySQL mysql;
        mysql.set_path("tcp://127.0.0.1:3306");
        mysql.set_user_name("root");
        mysql.set_user_password("zxcv123456789");
        mysql.set_database_name("test");
        
        // 连接数据库
        mysql.connect();
        
        // 创建表
        std::cout << "创建 users 表..." << std::endl;
        mysql.execute("DROP TABLE IF EXISTS users");
        mysql.execute("CREATE TABLE IF NOT EXISTS users ("
                      "id INT AUTO_INCREMENT PRIMARY KEY, "
                      "account VARCHAR(255) NOT NULL, "
                      "password_hash VARCHAR(255) NOT NULL, "
                      "nick_name VARCHAR(255), "
                      "signature TEXT, "
                      "avatar_url TEXT, "
                      "user_type INT DEFAULT 0, "
                      "user_status INT DEFAULT 0, "
                      "last_device_type INT DEFAULT 0, "
                      "last_ip_address VARCHAR(255), "
                      "last_login_time DATETIME, "
                      "last_logout_time DATETIME)");
        
        // 插入测试数据
        std::cout << "插入测试数据..." << std::endl;
        mysql.execute("INSERT INTO users (account, password_hash, nick_name) VALUES ('test_user', 'password_hash', '测试用户')");
        
        // 查询数据
        std::cout << "查询测试数据..." << std::endl;
        auto results = mysql.query("SELECT id, account, nick_name FROM users");
        
        // 显示查询结果
        std::cout << "查询结果:" << std::endl;
        for (const auto& row : results) {
            std::cout << "ID: " << row[0] << ", 账号: " << row[1] << ", 昵称: " << row[2] << std::endl;
        }
        
        std::cout << "MySQL 测试完成" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "MySQL 测试异常: " << e.what() << std::endl;
    }
}