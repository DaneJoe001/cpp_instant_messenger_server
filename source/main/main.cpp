#include <iostream>

#include <core/network/base_network.hpp>
#include <main/check_main.hpp>

#define CHECK 5
int main(void)
{

    set_test_config();

#if CHECK==0
    std::cout << "Check DaneJoe001's log" << std::endl;
    check_danejoe_log();
#endif

#if CHECK==1
    std::cout << "Check Config Manager" << std::endl;
    check_config_manager();
#endif

#if CHECK==2
    std::cout << "Check UtilTime" << std::endl;
    check_util_time();
#endif

#if CHECK==3
    std::cout << "Check Config Database" << std::endl;
    check_config_database();
#endif

#if CHECK==4
    std::cout << "Check MySQL" << std::endl;
    check_mysql();
#endif

#if CHECK==5
    std::cout << "Check SQLite" << std::endl;
    check_sqlite();
#endif
    return 0;
}