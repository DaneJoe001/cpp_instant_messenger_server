#include <iostream>

#include "main/check_main.hpp"
#include "core/log/manage_log.hpp"
#include "core/database/database_sqlite.hpp"
#include "core/database/database_mysql.hpp"
#include "core/log/log_danejoe.hpp"
#include "core/config/manage_config.hpp"
#include "core/config/config_log.hpp"
#include "core/util/util_time.hpp"
#include "core/config/config_database.hpp"
#include "core/util/util_json.hpp"
void check_sqlite()
{
    try
    {
        std::cout << "[TEST] 测试 SQLite 数据库..." << std::endl;
        std::shared_ptr<BaseLogger> logger = ManageLog::get_instance().get_logger<LogDaneJoe>("TEST");

        DatabaseSQLite sqlite(logger);

        std::cout << ConfigDatabase(ManageConfig::get_instance()).get_config_str() << std::endl;

        BaseDatabase::DatabaseConfig database_config = ConfigDatabase(ManageConfig::get_instance()).get_config();

        sqlite.set_config(database_config);
        sqlite.connect();
        sqlite.execute("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, account TEXT, password_hash TEXT, nick_name TEXT, signature TEXT, avatar_url TEXT, user_type INTEGER, user_status INTEGER, last_device_type INTEGER, last_ip_address TEXT, last_login_time TEXT, last_logout_time TEXT)");
        std::cout << "SQLite 测试完成" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "[TEST] SQLite 测试异常: " << e.what() << std::endl;
    }
}

void check_mysql()
{
    try
    {
        std::cout << "[TEST] 测试 MySQL 数据库..." << std::endl;
        DatabaseMySQL mysql(ManageLog::get_instance().get_logger<LogDaneJoe>("TEST"));
        mysql.set_path("tcp://127.0.0.1:3306");
        mysql.set_user_name("root");
        mysql.set_user_password("zxcv123456789");
        mysql.set_database_name("test");

        // 连接数据库
        mysql.connect();

        // 创建表
        std::cout << "[TEST] 创建 users 表..." << std::endl;
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
        std::cout << "[TEST] 插入测试数据..." << std::endl;
        mysql.execute("INSERT INTO users (account, password_hash, nick_name) VALUES ('test_user', 'password_hash', '测试用户')");

        // 查询数据
        std::cout << "[TEST] 查询测试数据..." << std::endl;
        auto results = mysql.query("SELECT id, account, nick_name FROM users");

        // 显示查询结果
        std::cout << "[TEST] 查询结果:" << std::endl;
        for (const auto& row : results)
        {
            std::cout << "ID: " << row[0] << ", 账号: " << row[1] << ", 昵称: " << row[2] << std::endl;
        }

        std::cout << "[TEST] MySQL 测试完成" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "[TEST] MySQL 测试异常: " << e.what() << std::endl;
    }
}

void check_danejoe_log()
{
    ManageLog& manage_log = ManageLog::get_instance();

    std::cout << "[TEST] 测试 DaneJoe 日志系统..." << std::endl;
    manage_log.get_logger<LogDaneJoe>("TestLog")->info("测试日志");
    manage_log.get_logger<LogDaneJoe>("")->info("默认日志");
    std::cout << "[TEST] 日志系统测试完毕" << std::endl;
}

void check_config_manager()
{
    ManageConfig& manage_config = ManageConfig::get_instance();
    BaseLogger::LogConfig log_config = ConfigLog(manage_config).get_config();

    ManageLog& manage_log = ManageLog::get_instance();
    manage_log.add_logger<LogDaneJoe>(log_config);
    manage_log.get_logger<LogDaneJoe>("TEST")->info("测试日志");
    manage_log.get_logger<LogDaneJoe>("")->info("默认日志");
    std::cout << "[INFO] :测试完毕" << std::endl;


    std::cout << ConfigLog(manage_config).get_config_str() << std::endl;
}

void check_util_time()
{
    std::cout << "[TIME] " + TIME_STR << std::endl;
}

void check_config_database()
{
    ManageConfig& manage_config = ManageConfig::get_instance();


    BaseDatabase::DatabaseConfig database_config = ConfigDatabase(manage_config).get_config();
    std::cout << ConfigDatabase(manage_config).get_config_str() << std::endl;
}

void check_util_json()
{
    ManageConfig& manage_config = ManageConfig::get_instance();
    // manage_config.set_config_path("./config/config.json");
    manage_config.set_config_path("/mnt/e/personal_code/code_cpp_project/cpp_instant_messenger_server/config/config.json");
    manage_config.load_config();

    ConfigDatabase config_database(manage_config);
    std::cout << config_database.get_config_str() << std::endl;

    ConfigLog config_log(manage_config);
    std::cout << config_log.get_config_str() << std::endl;

    // UtilJson util_json;
    // util_json.load_json_from_path("/mnt/e/personal_code/code_cpp_project/cpp_instant_messenger_server/config/TEST.json");
    // std::string result = util_json.get_value<std::string>("name", "not_found");
    // std::cout << "[INFO] " << result << std::endl;
    // util_json.save_json_to_path("/mnt/e/personal_code/code_cpp_project/cpp_instant_messenger_server/config/TEST2.json");

}