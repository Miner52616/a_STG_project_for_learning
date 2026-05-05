#pragma once
#include <sol/sol.hpp>

class SaveData
{
public:
    bool cleared_=false;
    int high_score_=0;
};

class LuaManager
{
public:
    sol::state lua_;

    LuaManager();
    void loadScript(const std::string& path);
    SaveData loadSave();
    void writeSave(const SaveData& data);
};