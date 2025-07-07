#include <iostream>

#include <core/network/base_network.hpp>
#include <main/check_main.hpp>

#define CHECK 0
int main(void)
{

#if CHEKC==0
    std::cout << "Check DaneJoe001's log" << std::endl;
    check_danejoe_log();
#endif
    return 0;
}