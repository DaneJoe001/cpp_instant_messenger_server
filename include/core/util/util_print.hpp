#pragma once

#include <string>
#include <mutex>
#include <unordered_map>
#include <algorithm>
#include <atomic>

/**
 * @brief 输出工具类(实现线程安全输出)
 * @todo 拓展到模板类
 * @todo 替换所有的控制台输出部分
 */
class UtilPrint
{
public:
    enum class AddPosition
    {
        LEFT,
        RIGHT,
        MIRRORED,
        LEFT_RIGHT
    };
    enum class BracketType
    {
        /// @brief 无括号
        NONE,
        /// @brief 方括号[]
        SQUARE,
        /// @brief 圆括号()
        ROUND,
        /// @brief 大括号{}
        CURLY,
        /// @brief 尖括号<>
        ANGLE,
        /// @brief 竖线|
        VERTICAL
    };
    enum class LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };
    struct OutputSetting
    {
        bool is_time_visible = true;
        bool is_level_visible = true;
        bool is_line_visible = false;
        bool is_function_visible = false;
        bool is_file_name_visible = false;
    };
public:
    /**
     * @brief 获取字符串
     * @param map std::unordered_map<std::string, std::string>类型
     * @note 考虑通过拓展string类来实现以std::string(std::unordered_map<std::string, std::string>)构建字符串
     * 或者继承string类来实现(qDebug类)
     */
    static std::string get_str(std::unordered_map<std::string, std::string> map);
    static std::string get_log_str(LogLevel level, std::string info, OutputSetting output_setting);
    static std::string add_str(std::string str, std::string addition, AddPosition pos = AddPosition::RIGHT);
    /// @todo 考虑替换掉非日志部分的控制台输出
    /// @todo 测试用调试信息输出
    static void print(std::string info);
    static void print(std::string head, std::string info);
    static void print(LogLevel level, std::string info, OutputSetting output_setting);
    static void set_log_level(LogLevel level);
    static std::string add_bracket(BracketType type, std::string str);

private:
    static std::mutex m_stdout_mutex;
    static std::atomic<LogLevel> m_log_level;
};