#include <iostream>

#include "core/util/util_print.hpp"
#include "core/util/util_time.hpp"

std::atomic<UtilPrint::LogLevel> UtilPrint::m_log_level = UtilPrint::LogLevel::TRACE;

std::mutex UtilPrint::m_stdout_mutex;

std::string UtilPrint::get_str(std::unordered_map<std::string, std::string> map)
{
    /// @todo 实现更好的格式化效果,如对齐以及间距等
    std::string result;
    for (auto& item : map)
    {
        result += add_bracket(UtilPrint::BracketType::SQUARE,
            item.first + ":"
            + item.second);
    }
    return result;
}

std::string UtilPrint::get_log_str(LogLevel level, std::string info, OutputSetting output_setting)
{
    std::string log_level_str;
    switch (level)
    {
    case LogLevel::TRACE:
        log_level_str = "[TRACE]";
        break;
    case LogLevel::DEBUG:
        log_level_str = "[DEBUG]";
        break;
    case LogLevel::INFO:
        log_level_str = "[INFO]";
        break;
    case LogLevel::WARN:
        log_level_str = "[WARN]";
        break;
    case LogLevel::ERROR:
        log_level_str = "[ERROR]";
        break;
    case LogLevel::FATAL:
        log_level_str = "[FATAL]";
        break;
    default:
        log_level_str = "[UNKNOWN]";
    }
    /// @brief 拼接日志字符串
    std::string log_str;
    if (output_setting.is_time_visible)
    {
        log_str += add_bracket(BracketType::SQUARE, UtilTime::get_time_str());
        log_str += " ";
    }
    if (output_setting.is_level_visible)
    {
        log_str += log_level_str + " ";
    }
    if (output_setting.is_file_name_visible)
    {
        log_str += add_bracket(BracketType::SQUARE, __FILE__);
        log_str += " ";
    }
    if (output_setting.is_line_visible)
    {
        log_str += add_bracket(BracketType::SQUARE, std::to_string(__LINE__));
        log_str += " ";
    }
    if (output_setting.is_function_visible)
    {
#ifdef MSVC
        log_str += add_bracket(BracketType::SQUARE, __FUNCDNAME__);
#else
        log_str += add_bracket(BracketType::SQUARE, __PRETTY_FUNCTION__);
#endif
        log_str += " ";
    }
    return log_level_str + " " + info;
}

std::string UtilPrint::add_str(std::string str, std::string addition, AddPosition pos)
{
    std::string temp = addition;
    switch (pos)
    {
    case AddPosition::LEFT:
        return addition + str;
    case AddPosition::RIGHT:
        return str + addition;
    case AddPosition::LEFT_RIGHT:
        return addition + str + addition;
    case AddPosition::MIRRORED:
        std::reverse(addition.begin(), addition.end());
        return addition + str + temp;
    default:
        return str;
    }
}

std::string UtilPrint::add_bracket(BracketType type, std::string str)
{
    switch (type)
    {
    case BracketType::SQUARE:
        return "[" + str + "]";
    case BracketType::ROUND:
        return "(" + str + ")";
    case BracketType::CURLY:
        return "{" + str + "}";
    case BracketType::ANGLE:
        return "<" + str + ">";
    case BracketType::VERTICAL:
        return "|" + str + "|";
    default:
        return str;
    }
}

void UtilPrint::print(std::string head, std::string info)
{
    std::lock_guard<std::mutex> lock(m_stdout_mutex);
    std::cout << head << " " << info << std::endl;
}
void UtilPrint::print(LogLevel level, std::string info, OutputSetting output_setting)
{
    std::lock_guard<std::mutex> lock(m_stdout_mutex);
    std::cout << get_log_str(level, info, output_setting) << std::endl;
}

void UtilPrint::print(std::string info)
{
    std::lock_guard<std::mutex> lock(m_stdout_mutex);
    std::cout << info << std::endl;
}
void UtilPrint::set_log_level(LogLevel level)
{
    m_log_level.store(level);
}