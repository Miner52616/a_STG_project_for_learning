#pragma once
#include <memory>
#include <string>
#include <sol/sol.hpp>

class FrameInformation;

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
    bool key_frame_interpolation_=false;
};

class LuaManager
{
private:
    sol::state lua_;

public:
    LuaManager();

    sol::state& lua();
    void loadScript(const std::string& path);
    SaveData loadSave();
    Debug loadDebug();
    void writeSave(const SaveData& data);
    void writeReplay(const std::vector<FrameInformation>& replay,const unsigned int& seed);
};