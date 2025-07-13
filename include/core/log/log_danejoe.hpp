#pragma once

#include <fstream>
#include <mutex>

#include "core/log/base_log.hpp"

/// @todo 引入线程安全，调整日志函数参数格式

/**
 * @class LogDaneJoe
 * @brief 自定义日志类
 */
class LogDaneJoe : public BaseLogger
{
public:
    LogDaneJoe() = default;
    /**
     *  @brief 构造函数
     *  @param config 日志配置
     */
    LogDaneJoe(const LogConfig& config);
    /**
     * @brief 调试日志
     * @param log_info 日志信息
     */
    void debug(const std::string& log_info) override;
    /**
     * @brief 错误日志
     * @param log_info 日志信息
     */
    void error(const std::string& log_info) override;
    /**
     * @brief 信息日志
     * @param log_info 日志信息
     */
    void fatal(const std::string& log_info) override;
    /**
     * @brief 警告日志
     * @param log_info 日志信息
     */
    void warn(const std::string& log_info) override;
    /**
     * @brief 信息日志
     * @param log_info 日志信息
     */
    void info(const std::string& log_info) override;
    /**
     * @brief 跟踪日志
     * @param log_info 日志信息
     */
    void trace(const std::string& log_info) override;
private:
    /**
     *  @brief 打开日志文件
     *  @return 是否成功打开
     */
    bool open();
    /**
     *  @brief 输出日志
     *  @param level 日志等级
     *  @param log_info 日志信息
     */
    void output(LogLevel level, const std::string& log_info);
private:
    /// @brief 日志文件流
    std::ofstream m_file_out;
    /// @brief 文件输出锁
    std::mutex m_file_mutex;
};