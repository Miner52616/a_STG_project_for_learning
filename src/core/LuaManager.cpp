#include "core/LuaManager.h"
#include "packages/FrameInformation.h"
#include <sol/sol.hpp>
#include <fstream>
#include <iostream>
//#include "lua_packages/LuaBulletContext.h"
#include "lua_packages/LuaPackages.h"
#include "lua_packages/LuaEntity.h"
#include "lua_packages/LuaBatch.h"
#include "packages/BulletConfig.h"
#include "packages/EffectConfig.h"
#include "packages/BatchConfig.h"
#include "packages/LuaDependency.h"
#include "core/Clock.h"

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

    registerLua();
    /*
    lua_.new_usertype<LuaBulletContext>
    (
        "BulletContext",
        "getPosition",&LuaBulletContext::getPosition,
        "spawnBullet",&LuaBulletContext::spawnBullet,
        "random",&LuaBulletContext::random
    );
    */
}

void LuaManager::registerLua()
{
    registerSFML();
    registerPackages();
    registerLuaPackages();
}

void LuaManager::registerSFML()
{
    lua_.new_usertype<sf::Vector2f>
    (
        "Vector2f",
        sol::constructors<sf::Vector2f(float,float)>(),
        "x",&sf::Vector2f::x,
        "y",&sf::Vector2f::y
    );

    lua_.new_usertype<sf::Vector2i>
    (
        "Vector2i",
        sol::constructors<sf::Vector2i(int,int)>(),
        "x",&sf::Vector2i::x,
        "y",&sf::Vector2i::y
    );

    lua_.new_usertype<sf::Texture>
    (
        "Texture",
        sol::no_constructor
    );
}

void LuaManager::registerPackages()
{
    lua_.new_usertype<Clock>
    (
        "Clock",
        sol::no_constructor,
        "count",&Clock::count,
        "reset",&Clock::reset,
        "set_ready",&Clock::set_ready,
        "get_condition",&Clock::get_condition,
        "get_target",&Clock::get_target,
        "set_target",&Clock::set_target
    );

    lua_.new_enum<BulletClasses>
    (   
        "BulletClasses",
        {
            {"LinearBullet",BulletClasses::LinearBullet},
            {"PlayerBullet",BulletClasses::PlayerBullet},
            {"DirectBullet1",BulletClasses::DirectBullet1},
            {"DirectBullet2",BulletClasses::DirectBullet2},
            {"PlayerAimBullet",BulletClasses::PlayerAimBullet},
            {"DirectBullet3",BulletClasses::DirectBullet3},
            {"GravityBullet",BulletClasses::GravityBullet},
            {"RotateBullet1",BulletClasses::RotateBullet1},
            {"Behavior_DirectBullet1",BulletClasses::Behavior_DirectBullet1},
            {"PhaseCenterRotateBullet1",BulletClasses::PhaseCenterRotateBullet1},
            {"PhaseCenterRotateExpandBullet1",BulletClasses::PhaseCenterRotateExpandBullet1},
            {"VoidUpdate",BulletClasses::VoidUpdate}
        }
    );

    lua_.new_enum<BulletBehavior>
    (
        "BulletBehavior",
        {
            {"Fix",BulletBehavior::Fix},
            {"Rotate",BulletBehavior::Rotate},
            {"Direct",BulletBehavior::Direct}
        }
    );

    lua_.new_enum<BulletSize>
    (
        "BulletSize",
        {
            {"Small",BulletSize::Small},
            {"Big",BulletSize::Big},
            {"Large",BulletSize::Large}
        }
    );

    lua_.new_usertype<BulletConfig>
    (
        "BulletConfig",
        sol::constructors<BulletConfig(sf::Texture& texture)>(),
        "x_",&BulletConfig::x_,
        "v_",&BulletConfig::v_,
        "a_",&BulletConfig::a_,
        "a2_",&BulletConfig::a2_,
        "v2_",&BulletConfig::v2_,
        "v3_",&BulletConfig::v3_,
        "rotate_angle_",&BulletConfig::rotate_angle_,
        "rotate_angle2_",&BulletConfig::rotate_angle2_,
        "r_",&BulletConfig::r_,
        "r2_",&BulletConfig::r2_,
        "damage_",&BulletConfig::damage_,
        "angle_",&BulletConfig::angle_,
        "angle2_",&BulletConfig::angle2_,
        "bullet_num_",&BulletConfig::bullet_num_,
        "random_son_direction_",&BulletConfig::random_son_direction_,
        "not_clear_",&BulletConfig::not_clear_,
        "self_phase_",&BulletConfig::self_phase_,
        "color_alpha_",&BulletConfig::color_alpha_,
        "clock1_",&BulletConfig::clock1_,
        "clock2_",&BulletConfig::clock2_,
        "clock3_",&BulletConfig::clock3_,
        "direction_",&BulletConfig::direction_,
        "direction2_",&BulletConfig::direction2_,
        "spawn_point_",&BulletConfig::spawn_point_,
        "center_point_",&BulletConfig::center_point_,
        "center_point2_",&BulletConfig::center_point2_,
        "target_point_",&BulletConfig::target_point_,
        "target_point2_",&BulletConfig::target_point2_,
        "target_point3_",&BulletConfig::target_point3_,
        "bulletclass_",&BulletConfig::bulletclass_,
        "bulletbehavior_",&BulletConfig::bulletbehavior_,
        "bulletbehavior2_",&BulletConfig::bulletbehavior2_,
        "bulletsize_",&BulletConfig::bulletsize_,
        "bullet_index_",&BulletConfig::bullet_index_,
        "bullet_index2_",&BulletConfig::bullet_index2_
    );

    lua_.new_enum<EffectType>
    (
        "EffectType",
        {
            {"LeiTan_Air",EffectType::LeiTan_Air},
            {"Bullet_Air",EffectType::Bullet_Air},
            {"PlayerBullet_Air",EffectType::PlayerBullet_Air},
            {"VoidUpdate",EffectType::VoidUpdate}
        }
    );

    lua_.new_enum<OverlayType>
    (
        "OverlayType",
        {
            {"Picture_Overlay",OverlayType::Picture_Overlay},
            {"Text_Overlay",OverlayType::Text_Overlay}
        }
    );

    lua_.new_usertype<EffectConfig>
    (
        "EffectConfig",
        sol::constructors<EffectConfig(sf::Texture& texture)>(),
        "spawn_point_",&EffectConfig::spawn_point_,
        "effecttype_",&EffectConfig::effecttype_,
        "time_",&EffectConfig::time_,
        "a_",&EffectConfig::a_,
        "v_",&EffectConfig::v_,
        "v2_",&EffectConfig::v2_,
        "color_alpha_",&EffectConfig::color_alpha_,
        "direction_",&EffectConfig::direction_,
        "texture_",&EffectConfig::texture_,
        "texturelist_size_",&EffectConfig::texturelist_size_,
        "current_texture_num_",&EffectConfig::current_texture_num_,
        "random_rotate_",&EffectConfig::random_rotate_,
        "effect_index_",&EffectConfig::effect_index_,
        "isText",&EffectConfig::isText,
        //"font_",&EffectConfig::font_,
        "text_",&EffectConfig::text_,
        "text_size_",&EffectConfig::text_size_
    );

    lua_.new_usertype<BatchConfig>
    (
        "BatchConfig",
        sol::constructors<BatchConfig()>(),
        "target_time_",&BatchConfig::target_time_,
        "target_time2_",&BatchConfig::target_time2_,
        "target_time3_",&BatchConfig::target_time3_
    );

    lua_.new_usertype<LuaDependency>
    (
        "LuaDependency",
        //sol::constructors<LuaDependency(LuaResource,LuaEntity)>(),
        "resource_",&LuaDependency::resource_,
        "entity_",&LuaDependency::entity_
    );
}

void LuaManager::registerLuaPackages()
{
    lua_.new_usertype<LuaResource>
    (
        "Resource",
        "addBullet",&LuaResource::addBullet,
        "addBatch",&LuaResource::addBatch
    );

    lua_.new_usertype<LuaEntity>
    (
        "Entity",
        "getPosition",&LuaEntity::getPosition
    );

    lua_.new_usertype<LuaBatch>
    (
        "LuaBatch",
        "bundle_config",&LuaBatch::bundle_config,
        "set_add_finished",&LuaBatch::set_add_finished
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
        sol::load_result script = lua_.load_file("lua_files/save.lua");

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
    loadScript("lua_files/debug.lua");

    sol::table debug_table=(lua_)["debug"];
    debug.hitbox_exist_=debug_table["hitbox_exist"];
    debug.debug_information_=debug_table["debug_information"];
    //debug.key_frame_interpolation_=debug_table["key_frame_interpolation"];

    return debug;
}

void LuaManager::writeSave(const SaveData& data)
{
    std::ofstream file("lua_files/save.lua");

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