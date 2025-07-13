#include <iostream>

#include "main/check_main.hpp"
#include "main/check_data.hpp"
#include "core/network/base_network.hpp"
#include "core/util/util_print.hpp"

static UtilPrint::OutputSetting g_output_setting;

#define CHECK 9
int main(void)
{
    init_users();
#if CHECK==0
    UtilPrint::print("[INFO]", "检查日志系统");
    check_danejoe_log();
#endif

#if CHECK==1
    UtilPrint::print("[INFO]", "检查配置管理");
    check_config_manager();
#endif

#if CHECK==2
    UtilPrint::print("[INFO]", "检查时间系统");
    check_util_time();
#endif

#if CHECK==3
    UtilPrint::print("[INFO]", "检查数据库配置");
    check_config_database();
#endif

#if CHECK==4
    UtilPrint::print("[INFO]", "检查MySQL");
    check_mysql();
#endif

#if CHECK==5
    UtilPrint::print("[INFO]", "检查SQLite");
    check_sqlite();
#endif

#if CHECK==6
    UtilPrint::print("[INFO]", "检查JSON");
    check_util_json();
#endif

#if CHECK==7
    UtilPrint::print("[INFO]", "检查日志系统");
    check_danejoe_log();
#endif

#if CHECK==8
    UtilPrint::print("[INFO]", "检查打印工具");
    // check_util_print();
    UtilPrint::print("hello world");
    std::cout << UtilPrint::add_bracket(UtilPrint::BracketType::SQUARE, "TEST") << std::endl;
    UtilPrint::print(UtilPrint::LogLevel::TRACE, "日志测试", UtilPrint::OutputSetting());
#endif
#if CHECK==9
    UtilPrint::print(UtilPrint::LogLevel::INFO, "测试用户数据访问", g_output_setting);
    check_access_user();
#endif
}