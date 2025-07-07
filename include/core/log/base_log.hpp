#include <string>
/**
 * @class BaseLogger
 * @brief 日志基类
 */
class BaseLogger
{
    enum class LogLevel
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };
public:
    BaseLogger() = default;
    virtual void trace(std::string log_name,std::string log) = 0;
    virtual void debug(std::string log_name) = 0;
    virtual ~BaseLogger() = default;
};