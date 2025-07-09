#include <iostream>

#include "core/util/util_json.hpp"

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
#if CONSOLE_OUTPUT_LEVEL <= 3
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
        std::cout << "[ERROR] JSON解析错误" << std::endl;
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << "[ERROR] JSON解析错误" << e.what() << std::endl;
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
            std::cout << "[ERROR] JSON文件打开失败" << std::endl;
            return false;
        }
        //添加缩进
        json_file << m_json.dump(4);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cout << "[ERROR] JSON文件保存失败" << std::endl;
        return false;
    }
    return false;
}