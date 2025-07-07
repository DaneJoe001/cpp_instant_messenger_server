# 即时通讯服务器数据库开发日志

## 目录
1. [项目概述](#项目概述)
2. [数据库设计](#数据库设计)
3. [开发问题记录](#开发问题记录)
   - [SQLite 实现问题](#sqlite-实现问题)
   - [MySQL 连接问题](#mysql-连接问题)
   - [MySQL 段错误问题](#mysql-段错误问题)
4. [待办事项](#待办事项)

## 项目概述

本项目是一个使用 C++ 开发的即时通讯服务器，支持 SQLite 和 MySQL 两种数据库后端。数据库模块采用抽象工厂模式设计，通过 `BaseDatabase` 抽象类定义统一接口，再由具体的 `DatabaseSQLite` 和 `DatabaseMySQL` 类实现不同数据库的操作。

## 数据库设计

### 数据库架构

```
BaseDatabase (抽象基类)
  ├── DatabaseSQLite (SQLite 实现)
  └── DatabaseMySQL (MySQL 实现)
```

### 主要表结构

#### 用户表 (users)

| 字段名 | 类型 | 说明 |
|--------|------|------|
| id | INT AUTO_INCREMENT | 主键 |
| account | VARCHAR(255) | 用户账号 |
| password_hash | VARCHAR(255) | 密码哈希 |
| nick_name | VARCHAR(255) | 昵称 |
| signature | TEXT | 个性签名 |
| avatar_url | TEXT | 头像URL |
| user_type | INT | 用户类型 |
| user_status | INT | 用户状态 |
| last_device_type | INT | 最后登录设备类型 |
| last_ip_address | VARCHAR(255) | 最后登录IP |
| last_login_time | DATETIME | 最后登录时间 |
| last_logout_time | DATETIME | 最后登出时间 |

## 开发问题记录

### SQLite 实现问题

#### 问题描述
SQLite 数据库实现中使用了不正确的初始化方式：
```cpp
SQLite::Database m_database = nullptr;
```
这种方式不正确，因为 `SQLite::Database` 是一个类，不能直接赋值为 `nullptr`。

#### 解决方案
使用 `std::unique_ptr` 管理 `SQLite::Database` 对象：
```cpp
std::unique_ptr<SQLite::Database> m_database;
```

并在构造函数中初始化：
```cpp
DatabaseSQLite::DatabaseSQLite() : m_database(nullptr)
{
}
```

在 `connect()` 方法中创建数据库对象：
```cpp
m_database = std::make_unique<SQLite::Database>(m_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
```

#### 改进点
1. 使用智能指针自动管理资源
2. 添加异常处理
3. 添加空指针检查

### MySQL 连接问题

#### 问题描述
程序运行时出现 MySQL 连接错误：
```
Error connecting to MySQL database: Access denied for user 'root'@'localhost'
```

#### 原因分析
MySQL 服务器使用 `auth_socket` 认证插件，而不是密码认证。

#### 解决方案
1. 修改 MySQL 用户认证方式：
```sql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'zxcv123456789';
FLUSH PRIVILEGES;
```

2. 确保 `test` 数据库存在：
```sql
CREATE DATABASE IF NOT EXISTS test;
```

#### 改进点
1. 添加详细的连接日志
2. 增强错误处理和报告

### MySQL 段错误问题

#### 问题描述
程序在正常执行完所有数据库操作后，在退出时发生段错误。

#### 调试过程
使用 GDB 捕获段错误：
```bash
gdb -batch -ex "run" -ex "bt" ./instance_messenger_server
```

堆栈跟踪显示错误发生在 MySQL 驱动程序的静态析构函数中：
```
Program received signal SIGSEGV, Segmentation fault.
0x00000000000007b1 in ?? ()
#1  0x00007ffff7f4d251 in std::_Rb_tree<sql::SQLString, std::pair<sql::SQLString const, boost::shared_ptr<sql::mysql::MySQL_Driver> >, std::_Select1st<std::pair<sql::SQLString const, boost::shared_ptr<sql::mysql::MySQL_Driver> > >, std::less<sql::SQLString>, std::allocator<std::pair<sql::SQLString const, boost::shared_ptr<sql::mysql::MySQL_Driver> > > >::_M_erase(std::_Rb_tree_node<std::pair<sql::SQLString const, boost::shared_ptr<sql::mysql::MySQL_Driver> > >*) () from /lib/x86_64-linux-gnu/libmysqlcppconn.so.7
```

#### 原因分析
MySQL Connector/C++ 库使用静态实例管理驱动程序，在程序退出时，静态实例的析构顺序不确定，导致访问已释放的内存。

#### 解决方案
不使用静态驱动实例，改为直接创建新的驱动实例：
```cpp
// 不使用这种方式
// m_driver = std::unique_ptr<sql::mysql::MySQL_Driver>(sql::mysql::get_mysql_driver_instance());

// 改为使用这种方式
m_driver = std::unique_ptr<sql::mysql::MySQL_Driver>(new sql::mysql::MySQL_Driver());
```

#### 改进点
1. 避免使用静态驱动实例
2. 使用智能指针管理资源
3. 简化析构函数中的资源释放逻辑

## 待办事项

1. **实现参数化查询**：
   - 为 SQLite 和 MySQL 实现安全的参数化查询，避免 SQL 注入风险

2. **添加事务支持**：
   - 实现事务操作方法：`beginTransaction()`, `commit()`, `rollback()`

3. **完善数据访问层**：
   - 实现 `AccessUser` 类，封装用户相关的数据库操作

4. **添加连接池支持**：
   - 为高并发场景实现数据库连接池

5. **添加 ORM 支持**：
   - 实现简单的 ORM 功能，自动映射实体类和数据库表

6. **改进错误处理**：
   - 实现更详细的错误日志和异常处理机制

7. **添加数据库迁移工具**：
   - 实现数据库版本管理和迁移功能 