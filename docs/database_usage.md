# 数据库模块使用说明

## 概述

即时通讯服务器的数据库模块支持 SQLite 和 MySQL 两种数据库后端，通过统一的接口进行操作。本文档介绍如何使用数据库模块进行基本操作。

## 支持的数据库

- **SQLite**: 轻量级嵌入式数据库，适合单机部署或开发测试
- **MySQL**: 强大的关系型数据库，适合多用户、高并发场景

## 基本用法

### 导入必要的头文件

```cpp
#include <core/database/database_sqlite.hpp>  // 使用 SQLite
#include <core/database/database_mysql.hpp>   // 使用 MySQL
```

### SQLite 数据库操作示例

```cpp
// 创建 SQLite 数据库实例
DatabaseSQLite sqlite;

// 设置数据库文件路径
sqlite.set_path("database.db");

// 连接数据库
sqlite.connect();

// 执行 SQL 语句
sqlite.execute("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
sqlite.execute("INSERT INTO users (name) VALUES ('张三')");

// 查询数据
auto results = sqlite.query("SELECT id, name FROM users");

// 处理查询结果
for (const auto& row : results) {
    std::cout << "ID: " << row[0] << ", 姓名: " << row[1] << std::endl;
}
```

### MySQL 数据库操作示例

```cpp
// 创建 MySQL 数据库实例
DatabaseMySQL mysql;

// 设置连接参数
mysql.set_path("tcp://127.0.0.1:3306");
mysql.set_user_name("root");
mysql.set_user_password("password");
mysql.set_database_name("im_server");

// 连接数据库
mysql.connect();

// 执行 SQL 语句
mysql.execute("CREATE TABLE IF NOT EXISTS users (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255))");
mysql.execute("INSERT INTO users (name) VALUES ('张三')");

// 查询数据
auto results = mysql.query("SELECT id, name FROM users");

// 处理查询结果
for (const auto& row : results) {
    std::cout << "ID: " << row[0] << ", 姓名: " << row[1] << std::endl;
}
```

## 错误处理

数据库操作可能会抛出异常，建议使用 try-catch 块进行错误处理：

```cpp
try {
    DatabaseMySQL mysql;
    mysql.set_path("tcp://127.0.0.1:3306");
    mysql.set_user_name("root");
    mysql.set_user_password("password");
    mysql.set_database_name("im_server");
    mysql.connect();
    
    // 执行数据库操作...
} catch (const std::exception& e) {
    std::cerr << "数据库错误: " << e.what() << std::endl;
    
    // 获取更多错误信息
    std::cerr << "错误消息: " << mysql.error_message() << std::endl;
    std::cerr << "错误代码: " << mysql.error_code() << std::endl;
}
```

## 最佳实践

1. **使用参数化查询**：避免 SQL 注入风险
2. **合理管理连接**：在不需要时关闭连接
3. **使用事务**：对于多个相关操作，使用事务确保原子性
4. **异常处理**：始终使用 try-catch 捕获可能的异常
5. **资源管理**：使用智能指针管理资源，避免内存泄漏

## 注意事项

1. **MySQL 驱动实例**：避免使用静态驱动实例 `get_mysql_driver_instance()`，改为创建新实例 `new MySQL_Driver()`
2. **SQLite 文件路径**：确保应用程序有权限访问和修改 SQLite 数据库文件
3. **MySQL 认证**：确保 MySQL 服务器配置了正确的认证方式和用户权限

## 未来计划

- 参数化查询支持
- 事务支持
- 连接池
- ORM 支持
- 数据库迁移工具

## 常见问题

### Q: 连接 MySQL 时出现 "Access denied" 错误

**A**: 检查用户名和密码是否正确，以及 MySQL 服务器的认证方式。可能需要更改认证插件：

```sql
ALTER USER 'username'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
FLUSH PRIVILEGES;
```

### Q: 程序退出时出现段错误

**A**: 这可能是由于 MySQL 驱动程序的静态实例导致的。改为使用非静态实例：

```cpp
// 不使用
m_driver = std::unique_ptr<sql::mysql::MySQL_Driver>(sql::mysql::get_mysql_driver_instance());

// 改为
m_driver = std::unique_ptr<sql::mysql::MySQL_Driver>(new sql::mysql::MySQL_Driver());
``` 