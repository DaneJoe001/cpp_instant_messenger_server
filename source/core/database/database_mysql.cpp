#include <core/database/database_mysql.hpp>

DatabaseMySQL::DatabaseMySQL() : m_driver(nullptr), m_connection(nullptr) {}

DatabaseMySQL::~DatabaseMySQL()
{
    // 确保连接在析构前关闭
    if (m_connection)
    {
        try
        {
            std::cout << "关闭 MySQL 连接..." << std::endl;
            m_connection->close();
            m_connection.reset();
            std::cout << "MySQL 连接已关闭" << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "关闭 MySQL 连接时发生异常: " << e.what() << std::endl;
        }
    }

    // 不要显式释放驱动，让智能指针自己处理
    m_driver.reset();
}

void DatabaseMySQL::connect() {
    try
    {
        std::cout << "正在连接到 MySQL 数据库..." << std::endl;
        std::cout << "路径: " << m_path << std::endl;
        std::cout << "用户名: " << m_user_name << std::endl;
        std::cout << "数据库: " << m_database_name << std::endl;

        // 创建新的驱动实例，而不是使用静态实例
        m_driver = std::unique_ptr<sql::mysql::MySQL_Driver>(new sql::mysql::MySQL_Driver());

        // 创建连接
        m_connection = std::unique_ptr<sql::Connection>(m_driver->connect(m_path, m_user_name, m_user_password));

        // 检查连接是否成功
        if (!m_connection)
        {
            m_error_message = "无法创建数据库连接";
            std::cerr << "错误: " << m_error_message << std::endl;
            throw sql::SQLException(m_error_message);
        }

        // 设置要使用的数据库
        m_connection->setSchema(m_database_name);

        std::cout << "MySQL 数据库连接成功!" << std::endl;
    }
    catch (sql::SQLException& e)
    {
        m_error_message = e.what();
        m_error_code = std::to_string(e.getErrorCode());
        std::cerr << "MySQL 连接错误: " << m_error_message << std::endl;
        std::cerr << "MySQL 错误代码: " << m_error_code << std::endl;
        std::cerr << "SQL 状态: " << e.getSQLState() << std::endl;
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
            std::cerr << "错误: " << m_error_message << std::endl;
            return;
        }

        std::cout << "执行 SQL: " << statement << std::endl;

        // 对于非查询操作，使用 executeUpdate 而不是 executeQuery
        std::unique_ptr<sql::Statement> stmt(m_connection->createStatement());

        // 检查 SQL 语句类型
        if (statement.find("SELECT") == 0 || statement.find("select") == 0)
        {
            // 对于查询语句，使用 executeQuery
            std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(statement));
            std::cout << "查询执行成功" << std::endl;
        }
        else
        {
            // 对于非查询语句，使用 executeUpdate
            int updateCount = stmt->executeUpdate(statement);
            std::cout << "更新执行成功，影响行数: " << updateCount << std::endl;
        }

        // 检查警告
        const sql::SQLWarning* warning = stmt->getWarnings();
        if (warning != nullptr)
        {
            m_error_message = warning->getMessage();
            m_error_code = std::to_string(warning->getErrorCode());
            std::cerr << "执行语句警告: " << m_error_message << std::endl;
        }
    }
    catch (sql::SQLException& e)
    {
        m_error_message = e.what();
        m_error_code = std::to_string(e.getErrorCode());
        std::cerr << "MySQL 执行错误: " << m_error_message << std::endl;
        std::cerr << "SQL 状态: " << e.getSQLState() << std::endl;
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
            std::cerr << "错误: " << m_error_message << std::endl;
            return result;
        }

        std::cout << "查询 SQL: " << statement << std::endl;

        // 使用智能指针管理资源
        std::unique_ptr<sql::Statement> stmt(m_connection->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(statement));

        std::size_t column_count = res->getMetaData()->getColumnCount();
        std::cout << "查询结果列数: " << column_count << std::endl;

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

        std::cout << "查询结果行数: " << result.size() << std::endl;

        // 检查警告
        const sql::SQLWarning* warning = stmt->getWarnings();
        if (warning != nullptr)
        {
            m_error_message = warning->getMessage();
            m_error_code = std::to_string(warning->getErrorCode());
            std::cerr << "查询语句警告: " << m_error_message << std::endl;
        }
    }
    catch (sql::SQLException& e)
    {
        m_error_message = e.what();
        m_error_code = std::to_string(e.getErrorCode());
        std::cerr << "MySQL 查询错误: " << m_error_message << std::endl;
        std::cerr << "SQL 状态: " << e.getSQLState() << std::endl;
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