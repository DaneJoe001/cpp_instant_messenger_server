#pragma once

/// @brief 控制是否在在控制台输出
/// @note 配置类构建在日志类之前，就不打算引入日志管理了
/// @details 0:TRACE 1:DEBUG 2:INFO 3:WARN 4:ERROR 5:FATAL 6:OFF
/// CONSOLE_OUTPUT_LEVEL由cmake配置
#ifndef CONSOLE_OUTPUT_LEVEL
#define CONSOLE_OUTPUT_LEVEL 0
#endif

/// @brief 配置类控制台输出等级
/// @brief 控制台跟踪日志级别
#define CONSOLE_LEVEL_TRACE 0
/// @brief 控制台调试日志级别
#define CONSOLE_LEVEL_DEBUG 1
/// @brief 控制台信息日志级别
#define CONSOLE_LEVEL_INFO 2
/// @brief 控制台警告日志级别
#define CONSOLE_LEVEL_WARN 3
/// @brief 控制台错误日志级别
#define CONSOLE_LEVEL_ERROR 4
/// @brief 控制台严重日志级别
#define CONSOLE_LEVEL_FATAL 5