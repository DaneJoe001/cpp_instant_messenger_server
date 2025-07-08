#pragma once

#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

/// @brief 获取当前时间字符串
#define TIME_STR UtilTime::get_time_str()

/**
 * @class UtilTime
 * @brief 时间工具类
 */
class UtilTime
{
public:
    /**
     * @brief 获取当前时间字符串
     * @return std::string 时间字符串
     */
    static std::string get_time_str()
    {
        auto current_time = std::chrono::system_clock::now();
        std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
        std::tm* current_time_tm = std::localtime(&current_time_t);
        std::ostringstream oss;
        oss << std::put_time(current_time_tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

};