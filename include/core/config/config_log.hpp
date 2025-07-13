#pragma once

#include <string>

#include "core/log/base_log.hpp"

class ManageConfig;

/// @brief 日志项配置名称字符串
#define LOG_ITEM_STR std::string("log")
/// @brief 日志项路径字符串
#define LOG_PATH_STR std::string("path")
/// @brief 日志项是否输出控制台字符串
#define LOG_IS_CONSOLE_OUTPUT_STR std::string("is_console_output")
/// @brief 日志项是否输出文件字符串
#define LOG_IS_FILE_OUTPUT_STR std::string("is_file_output")
/// @brief 日志项名称字符串
#define LOG_NAME_STR std::string("name")
/// @brief 日志项控制台输出等级字符串
#define LOG_CONSOLE_LOG_LEVEL_STR std::string("console_log_level")
/// @brief 日志项文件输出等级字符串
#define LOG_FILE_LOG_LEVEL_STR std::string("file_log_level")
/// @brief 默认日志路径字符串
#define DEFAULT_LOG_PATH std::string("./log/")
/// @brief 默认日志名称字符串
#define DEFAULT_LOG_NAME std::string("default")
/// @brief 默认日志控制台输出等级
#define DEFAULT_LOG_CONSOLE_LOG_LEVEL CONSOLE_LEVEL_TRACE
/// @brief 默认日志文件输出等级
#define DEFAULT_LOG_FILE_LOG_LEVEL CONSOLE_LEVEL_TRACE
/// @brief 日志项是否输出文件
#define DEFAULT_LOG_IS_FILE_OUTPUT "1"
/// @brief 日志项是否输出控制台
#define DEFAULT_LOG_IS_CONSOLE_OUTPUT "1"

/**
 * @class ConfigLog
 * @brief 配置日志
 */
class ConfigLog
{
public:
    /**
     * @brief 构造函数
     * @param manage_config 配置管理器
     */
    ConfigLog(ManageConfig& manage_config);
    /**
     * @brief 获取配置
     * @return BaseLogger::LogConfig配置
     */
    BaseLogger::LogConfig get_config();
    /**
     * @brief 获取配置字符串
     * @return 配置字符串
     */
    std::string get_config_str();
private:
    /// @brief 配置管理器
    ManageConfig& m_manage_config;
};