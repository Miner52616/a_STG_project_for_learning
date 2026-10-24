#include "core/LuaManager.h"
#include "packages/FrameInformation.h"
#include <sol/sol.hpp>
#include <fstream>
#include <iostream>

LuaManager::LuaManager()
    //lua_(std::make_unique<sol::state>())
{
    lua_.open_libraries
    (
        sol::lib::base,
        sol::lib::package,
        sol::lib::math,
        sol::lib::table
    );

}

sol::state& LuaManager::lua()
{
    return lua_;
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

Debug LuaManager::loadDebug()
{
    Debug debug;
    loadScript("include/luas/debug.lua");

    sol::table debug_table=(lua_)["debug"];
    debug.hitbox_exist_=debug_table["hitbox_exist"];
    debug.debug_information_=debug_table["debug_information"];
    debug.key_frame_interpolation_=debug_table["key_frame_interpolation"];

    return debug;
}

void LuaManager::writeSave(const SaveData& data)
{
    std::ofstream file("include/luas/save.lua");

    if (!file.is_open())
    {
        std::cout<<"无法写入save.lua"<<std::endl;
        return;
    }

    file<<"return {\n";
    file<<"    high_score="<<data.high_score_<<",\n";
    file<<"    cleared="<<(data.cleared_ ? "true" : "false")<<"\n";
    file<<"}\n";
}

void LuaManager::writeReplay(const std::vector<FrameInformation>& replay,const unsigned int& seed)
{
    std::ofstream file("replay/replay.lua");
    file<<std::boolalpha;

    if (!file.is_open())
    {
        std::cout<<"无法写入replay"<<std::endl;
        return;
    }

    file<<"replay=\n";
    file<<"{\n";
    file<<"    seed="<<seed<<",\n";
    file<<"    frame_information=\n";
    file<<"    {\n";
    for(auto it=replay.begin();it!=replay.end();++it)
    {
        file<<"        {\n";
        file<<"            current_frame="<<it->current_frame_<<",\n";
        file<<"            key_Up="<<it->keys_.key_Up_<<",\n";
        file<<"            key_Down="<<it->keys_.key_Down_<<",\n";
        file<<"            key_Left="<<it->keys_.key_Left_<<",\n";
        file<<"            key_Right="<<it->keys_.key_Right_<<",\n";
        file<<"            key_LShift="<<it->keys_.key_LShift_<<",\n";
        file<<"            key_Z="<<it->keys_.key_Z_<<",\n";
        file<<"            key_X="<<it->keys_.key_X_<<",\n";
        file<<"        },\n";
    }
    file<<"    }\n";
    file<<"}\n";
}