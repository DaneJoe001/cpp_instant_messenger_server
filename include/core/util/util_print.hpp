#pragma once

#include <string>
#include <unordered_map>

/**
 * @brief 输出工具类
 * @todo 拓展到模板类
 */
class UtilPrint
{
public:
    /**
     * @brief 获取字符串
     * @param map std::unordered_map<std::string, std::string>类型
     * @note 考虑通过拓展string类来实现以std::string(std::unordered_map<std::string, std::string>)构建字符串
     * 或者继承string类来实现(qDebug类)
     */
    static std::string get_str(std::unordered_map<std::string, std::string> map)
    {
        /// @todo 实现更好的格式化效果,如对齐以及间距等
        std::string result;
        for (auto& item : map)
        {
            result += "[\"" + item.first + "\"]:[\"" + item.second + "\"]\n";
        }
        return result;
    }
    /// @todo 
    static void print(std::string head, std::string info)
    {
        std::cout << head << " " << info << std::endl;
    }
};