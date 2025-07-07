#include <core/database/database_sqlite.hpp>

// 确保 SQLite 命名空间的 Database 类已被正确前向声明或包含

DatabaseSQLite::DatabaseSQLite() : m_database(nullptr)
{
}

DatabaseSQLite::~DatabaseSQLite()
{
    // unique_ptr 会自动释放资源
}

void DatabaseSQLite::connect()
{
    try
    {
        // 使用 make_unique 创建 SQLite::Database 对象
        m_database = std::make_unique<SQLite::Database>(m_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    }
    catch (const SQLite::Exception& e)
    {
        m_error_message = e.what();
        m_error_code = std::to_string(e.getErrorCode());
        throw;
    }
}

void DatabaseSQLite::execute(const std::string& statement)
{
    try
    {
        if (!m_database)
        {
            m_error_message = "Database not connected";
            m_error_code = "-1";
            return;
        }
        
        m_database->exec(statement);
    }
    catch (const SQLite::Exception& e)
    {
        m_error_message = e.what();
        m_error_code = std::to_string(e.getErrorCode());
    }
}

std::vector<std::vector<std::string>> DatabaseSQLite::query(const std::string& statement)
{
    std::vector<std::vector<std::string>> result;
    
    try
    {
        if (!m_database)
        {
            m_error_message = "Database not connected";
            m_error_code = "-1";
            return result;
        }
        
        SQLite::Statement query(*m_database, statement);
        
        while (query.executeStep())
        {
            std::vector<std::string> row;
            for (int i = 0; i < query.getColumnCount(); i++)
            {
                row.push_back(query.getColumn(i).getString());
            }
            result.push_back(row);
        }
    }
    catch (const SQLite::Exception& e)
    {
        m_error_message = e.what();
        m_error_code = std::to_string(e.getErrorCode());
    }
    
    return result;
}

std::string DatabaseSQLite::error_message()
{
    return m_error_message;
}

std::string DatabaseSQLite::error_code()
{
    return m_error_code;
}