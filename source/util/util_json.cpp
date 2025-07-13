#include <iostream>

#include "core/util/util_json.hpp"
#include "core/util/util_print.hpp"

UtilJson::UtilJson(const nlohmann::json& json) :m_json(json) {}

bool UtilJson::load_json_from_path(const std::string& path)
{
    try
    {
        if (!std::filesystem::exists(path))
        {
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_ERROR
            std::cout << "[ERROR] 文件不存在" << std::endl;
#endif
            return false;
        }
        std::ifstream json_file(path);
        if (!json_file.is_open())
        {
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_ERROR
            std::cout << "[ERROR] 文件打开失败" << std::endl;
#endif
            return false;
        }
        json_file >> m_json;
        return true;
    }
    catch (const nlohmann::json::exception& e)
    {
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_ERROR
        std::cout << "[ERROR] JSON解析错误" << std::endl;
#endif
        return false;
    }
    catch (const std::exception& e)
    {
#if CONSOLE_OUTPUT_LEVEL <= CONSOLE_LEVEL_ERROR
        std::cout << "[ERROR] JSON解析错误" << std::endl;
#endif
        return false;
    }
}

bool UtilJson::load_json_from_string(const std::string& json_string)
{
    try
    {
        m_json = nlohmann::json::parse(json_string);
        return true;
    }
    catch (const nlohmann::json::exception& e)
    {
        UtilPrint::print(UtilPrint::LogLevel::ERROR, "JSON解析错误" + std::string(e.what()), UtilPrint::OutputSetting());
        return false;
    }
    catch (const std::exception& e)
    {
        UtilPrint::print(UtilPrint::LogLevel::ERROR, "JSON解析错误" + std::string(e.what()), UtilPrint::OutputSetting());
    }
    return false;
}

bool UtilJson::save_json_to_path(const std::string& path)
{
    try
    {
        std::ofstream json_file(path);
        if (!json_file.is_open())
        {
            UtilPrint::print(UtilPrint::LogLevel::ERROR, "JSON文件打开失败", UtilPrint::OutputSetting());
            return false;
        }
        /// @note 使用std::ofstream输出文件时存在不区分大小写的情况
        /// @brief 添加缩进
        json_file << m_json.dump(4);
        UtilPrint::print(UtilPrint::LogLevel::INFO, "JSON文件保存成功", UtilPrint::OutputSetting());
        return true;
    }
    catch (const std::exception& e)
    {
        UtilPrint::print(UtilPrint::LogLevel::ERROR, std::string("JSON文件保存失败") + e.what(), UtilPrint::OutputSetting());
        return false;
    }
    return false;
}

nlohmann::json UtilJson::get_json()
{
    return m_json;
}
