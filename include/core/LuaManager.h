#pragma once
#include <sol/sol.hpp>

class SaveData
{
public:
    bool cleared_=false;
    int high_score_=0;
};

class Debug
{
public:
    bool hitbox_exist_=false;
    bool debug_information_=false;
};

class LuaManager
{
public:
    sol::state lua_;

    LuaManager();
    void loadScript(const std::string& path);
    SaveData loadSave();
    Debug loadDebug();
    void writeSave(const SaveData& data);
};