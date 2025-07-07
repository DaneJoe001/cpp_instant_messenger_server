#pragma once

#include <string>

/**
 * @class BaseNetwork
 * @brief 网络基类
 */
class BaseNetwork {
public:
    /**
     * @brief 构造函数
     */
    BaseNetwork() = default;
    /**
     * @brief 析构函数
     */
    virtual void connect() = 0;
    /**
     * @brief 断开连接
     */
    virtual void disconnect() = 0;
    /**
     * @brief 发送数据
     */
    virtual void send(const std::string& message) = 0;
    virtual std::string receive() = 0;
    /**
     * @brief 设置主机地址
     * @param host 主机地址
     */
    void set_host(const std::string& host);
    /**
     * @brief 设置端口号
     * @param port 端口号
     */
    void set_port(const std::string& port);
    /**
     * @brief 设置用户名
     * @param user_name 用户名
     */
    void set_user_name(const std::string& user_name);
};