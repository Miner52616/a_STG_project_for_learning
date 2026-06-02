#include "core/LuaManager.h"
#include <fstream>

LuaManager::LuaManager()
{
    lua_.open_libraries
    (
        sol::lib::base,
        sol::lib::package,
        sol::lib::math,
        sol::lib::table
    );

}

void LuaManager::loadScript(const std::string& path)
{
    lua_.script_file(path);
}

SaveData LuaManager::loadSave()
{
    SaveData data;

    try
    {
        sol::load_result script = lua_.load_file("include/luas/save.lua");

        if (!script.valid())
        {
            std::cout << "save.lua 不存在，使用默认存档"<<std::endl;
            return data;
        }

        sol::protected_function_result result = script();

        if (!result.valid())
        {
            std::cout << "save.lua 执行失败"<<std::endl;
            return data;
        }

        sol::table save=result;

        // 读取
        data.high_score_=save["high_score"].get_or(0);
        data.cleared_=save["cleared"].get_or(false);
        std::cout<<"------------------------------------------"<<std::endl;
        std::cout<<"Load Save Data..."<<std::endl;
        std::cout<<"high score: "<<data.high_score_<<std::endl;
        std::cout<<"game cleared: "<<data.cleared_<<std::endl;
        std::cout<<"------------------------------------------"<<std::endl;
        std::cout<<std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "读取存档异常: " << e.what() << "\n";
    }

    return data;
}

void LuaManager::writeSave(const SaveData& data)
{
    std::ofstream file("include/luas/save.lua");

    if (!file.is_open())
    {
        std::cout << "无法写入 save.lua\n";
        return;
    }

    file<<"return {\n";
    file<<"    high_score="<<data.high_score_<<",\n";
    file<<"    cleared="<<(data.cleared_ ? "true" : "false")<<"\n";
    file<<"}\n";
}