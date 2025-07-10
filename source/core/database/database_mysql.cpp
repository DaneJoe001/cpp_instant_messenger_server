#include "core/database/database_mysql.hpp"
#include "core/util/util_time.hpp"
DatabaseMySQL::DatabaseMySQL(std::shared_ptr<BaseLogger> logger) : BaseDatabase(logger), m_connection(nullptr) {}

DatabaseMySQL::~DatabaseMySQL()
{
    // 确保连接在析构前关闭
    if (m_connection)
    {
        try
        {
            m_logger->info("关闭 MySQL 链接...");
            m_connection->close();
            m_connection.reset();
            m_logger->info("已关闭 MySQL 链接...");
        }
        catch (const std::exception& e)
        {
            m_logger->error("关闭 MySQL 链接时发生异常: " + std::string(e.what()));
        }
    }

    // 不要显式释放驱动，让智能指针自己处理
    m_driver.reset();
}

void DatabaseMySQL::connect() {
    try
    {
        m_logger->info("正在连接到 MySQL 数据库...");
        m_logger->info("数据库信息" + m_config.database_name + m_config.file_path() + m_config.user_name + m_config.user_password);

        // 创建新的驱动实例，而不是使用静态实例
        m_driver = std::unique_ptr<sql::mysql::MySQL_Driver>(new sql::mysql::MySQL_Driver());

        // 创建连接
        m_connection = std::unique_ptr<sql::Connection>(m_driver->connect(m_config.path, m_config.user_name, m_config.user_password));

        // 检查连接是否成功
        if (!m_connection)
        {
            m_logger->error("无法创建数据库连接");
            m_error_message = "无法创建数据库连接";
            std::cerr << "错误: " << m_error_message << std::endl;
            throw sql::SQLException(m_error_message);
        }

        // 设置要使用的数据库
        m_connection->setSchema(m_config.database_name);

        m_logger->info("MySQL 数据库连接成功!");
    }
    catch (sql::SQLException& e)
    {
        m_error_message = e.what();
        m_error_code = std::to_string(e.getErrorCode());
        m_logger->error("MySQL 错误码: " + m_error_code);
        m_logger->error("MySQL 错误信息: " + m_error_message);
        m_logger->error("MySQL 错误位置: " + std::string(e.getSQLState()));
        throw;
    }
}

void DatabaseMySQL::execute(const std::string& statement)
{
    try
    {
        if (!m_connection)
        {
            m_error_message = "数据库未连接";
            m_error_code = "-1";
            m_logger->error("MySQL 错误码: " + m_error_code);
            m_logger->error("MySQL 错误信息: " + m_error_message);
            return;
        }
        m_logger->trace("执行 SQL: " + statement);

        // 对于非查询操作，使用 executeUpdate 而不是 executeQuery
        std::unique_ptr<sql::Statement> stmt(m_connection->createStatement());

        // 检查 SQL 语句类型
        if (statement.find("SELECT") == 0 || statement.find("select") == 0)
        {
            // 对于查询语句，使用 executeQuery
            std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(statement));
            m_logger->trace("查询执行成功");
        }
        else
        {
            // 对于非查询语句，使用 executeUpdate
            int updateCount = stmt->executeUpdate(statement);
            m_logger->trace("更新执行成功,影响行数: " + std::to_string(updateCount));
        }

        // 检查警告
        const sql::SQLWarning* warning = stmt->getWarnings();
        if (warning != nullptr)
        {
            m_error_message = warning->getMessage();
            m_error_code = std::to_string(warning->getErrorCode());
            m_logger->warn("更新执行警告,错误码: " + m_error_code + ",错误信息: " + m_error_message);
        }
    }
    catch (sql::SQLException& e)
    {
        m_error_message = e.what();
        m_error_code = std::to_string(e.getErrorCode());
        m_logger->error("MySQL 执行错误: " + m_error_message);
        m_logger->error("SQL 状态: " + e.getSQLState());
    }
}

std::vector<std::vector<std::string>> DatabaseMySQL::query(const std::string& statement)
{
    std::vector<std::vector<std::string>> result;

    try
    {
        if (!m_connection)
        {
            m_error_message = "数据库未连接";
            m_error_code = "-1";
            m_logger->error("数据库未连接");
            return result;
        }

        m_logger->trace("查询 SQL: " + statement);

        // 使用智能指针管理资源
        std::unique_ptr<sql::Statement> stmt(m_connection->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(statement));

        std::size_t column_count = res->getMetaData()->getColumnCount();
        m_logger->trace("查询结果列数: " + std::to_string(column_count));

        // 处理结果
        while (res->next())
        {
            std::vector<std::string> row;
            for (size_t i = 1; i <= column_count; i++) // 注意：列索引从 1 开始
            {
                row.push_back(res->getString(i));
            }
            result.push_back(row);
        }

        m_logger->trace("查询结果行数: " + std::to_string(result.size()));

        // 检查警告
        const sql::SQLWarning* warning = stmt->getWarnings();
        if (warning != nullptr)
        {
            m_error_message = warning->getMessage();
            m_error_code = std::to_string(warning->getErrorCode());
            m_logger->warn("查询语句警告: " + m_error_message);
        }
    }
    catch (sql::SQLException& e)
    {
        m_error_message = e.what();
        m_error_code = std::to_string(e.getErrorCode());
        m_logger->error("查询语句错误: " + m_error_message);
        m_logger->error("SQL 状态: " + e.getSQLState());
    }

    return result;
}

std::string DatabaseMySQL::error_message()
{
    return m_error_message;
}

std::string DatabaseMySQL::error_code()
{
    return m_error_code;
}