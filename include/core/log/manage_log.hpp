#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "core/log/base_log.hpp"

/**
 * @class ManageLog
 * @brief 日志管理单例类
 */
class ManageLog
{
public:
    /**
     * @brief 获取单例对象
     */
    static ManageLog& get_instance();
    /**
     * @brief 获取日志对象
     * @details 当日志对象不存在时
     * @param log_name 日志名称
     */
    template<class T>
    std::shared_ptr<BaseLogger> get_logger(const std::string& log_name)
    {
        /// @todo: 当log is not exist, create one
        if (m_logger_map.find(log_name) == m_logger_map.end())
        {
            if (m_logger_map.find(m_default_log_config.name) == m_logger_map.end())
            {
                add_logger<T>(m_default_log_config);
            }
            return m_logger_map[m_default_log_config.name];
        }
        return m_logger_map[log_name];
    }
    /**
 * @brief 添加日志对象
 * @param log_config 日志配置
 * @tparam T 日志对象类型
 */
    template<class T>
    void add_logger(const BaseLogger::LogConfig& log_config)
    {
        if (m_logger_map.find(log_config.name) != m_logger_map.end())
        {
            return;
        }
        m_logger_map[log_config.name] = std::make_shared<T>(log_config);
    }
private:
    /**
     * @brief 构造函数
     */
    ManageLog();
    /**
     * @brief 析构函数
     */
    ~ManageLog() = default;
    /**
     * @brief
     */
    ManageLog(const ManageLog&) = delete;
    /*
     * @brief 移动赋值运算符
     */
    ManageLog(const ManageLog&&) = delete;
    /**
     * @brief 赋值运算符
     */
    ManageLog& operator=(const ManageLog&) = delete;
    /**
     * @brief 移动赋值运算符
     */
    ManageLog& operator=(const ManageLog&&) = delete;
private:
    /// @brief 日志记录器表
    std::unordered_map<std::string, std::shared_ptr<BaseLogger>> m_logger_map;
    BaseLogger::LogConfig m_default_log_config;
};