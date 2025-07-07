#include <iostream>

#include <core/network/base_network.hpp>
#include <main/check_main.hpp>

int main(void)
{
    try
    {
        // 测试 SQLite 数据库
        // check_sqlite();

        // 测试 MySQL 数据库
        check_mysql();

        std::cout << "所有测试完成，程序正常退出" << std::endl;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "程序异常: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "程序发生未知异常" << std::endl;
        return 2;
    }
}