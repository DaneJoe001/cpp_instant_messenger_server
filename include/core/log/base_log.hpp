#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>

#include "core/util/util_print.hpp"

/// @todo 考虑添加时间戳(以配置项或格式化字符串给出)
/**
 * @class BaseLogger
 * @brief 日志基类
 */
class BaseLogger
{
public:
    /**
     * @enum LogLevel
     * @brief 日志级别
     */
    enum class LogLevel :int32_t
    {
        /// @brief 追踪级别
        TRACE,
        /// @brief 调试级别
        DEBUG,
        /// @brief 信息级别
        INFO,
        /// @brief 警告级别
        WARN,
        /// @brief 错误级别
        ERROR,
        /// @brief 致命级别
        FATAL
    };
    /**
     * @struct LogConfig
     * @brief 日志配置结构体
     */
    struct LogConfig
    {
        /// @brief 日志路径
        std::string path;
        /// @brief 日志文件名(不带后缀)
        std::string name;
        /// @brief 是否在控制台输出
        bool is_console_output = 0;
        /// @brief 是否在文件输出
        bool is_file_output = 0;
        /// @brief 控制台日志级别
        LogLevel console_log_level;
        /// @brief 文件日志级别
        LogLevel file_log_level;
        /**
         * @return 文件路径
         */
        std::string file_path()const
        {
            return path + name + ".log";
        }
    };
public:
    /**
     * @brief 构造函数
     */
    BaseLogger() = default;
    /**
     * @brief 构造函数
     * @param config 日志配置结构体
     */
    BaseLogger(const LogConfig& config);
    /**
     *@brief 设置日志配置
     */
    void set_config(const LogConfig& config);
    /**
     * @brief 追踪日志纯虚函数
     * @details 当配置级别<DEBUG时输出
     */
    virtual void trace(const std::string& log_info) = 0;
    /**
     * @brief 调试日志纯虚函数
     */
    virtual void debug(const std::string& log_info) = 0;
    /**
     * @brief 信息日志纯虚函数
     */
    virtual void info(const std::string& log_info) = 0;
    /**
     * @brief 警告日志纯虚函数
     */
    virtual void warn(const std::string& log_info) = 0;
    /**
     * @brief 错误日志纯虚函数
     */
    virtual void error(const std::string& log_info) = 0;
    /**
     * @brief 致命日志纯虚函数
     */
    virtual void fatal(const std::string& log_info) = 0;
    virtual ~BaseLogger() = default;
    /**
     * @brief 设置时间是否可见
     * @param statu 是否可见
     */
    void set_time_is_visible(bool statu);
    /**
     * @brief 设置日志级别是否可见
     * @param statu 是否可见
     */
    void set_level_is_visible(bool statu);
    /**
     * @brief 设置文件名是否可见
     * @param statu 是否可见
     */
    void set_file_name_is_visible(bool statu);
    /**
     * @brief 设置行号是否可见
     * @param statu 是否可见
     */
    void set_line_is_visible(bool statu);
    /**
     * @brief 设置函数名是否可见
     * @param statu 是否可见
     */
    void set_function_is_visible(bool statu);
    UtilPrint::OutputSetting get_output_setting();
protected:
    /// @brief log配置
    LogConfig m_log_config;
    /// @brief 时间是否可见
    bool m_is_time_visible = true;
    /// @brief 日志级别是否可见
    bool m_is_level_visible = true;
    /// @brief 文件名是否可见
    bool m_is_file_name_visible = false;
    /// @brief 行号是否可见
    bool m_is_line_visible = false;
    /// @brief 函数名是否可见
    bool m_is_function_visible = false;
};