#pragma once
#include "phases/Phase.h"
#include <sol/sol.hpp>

class LuaManager;
class Resource;
class YellowPage;
class MidPhase;
class Enemy;
class Behavior;

class PEBFactory
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;
    

public:
    using BehaviorCreator=std::function<std::unique_ptr<Behavior>(Enemy*,const sol::table&)>;
    using PhaseCreator=std::function<std::unique_ptr<Phase>(const sol::table& phasescript)>;
private:
    std::unordered_map<std::string,BehaviorCreator> behaviorregistry_;
    std::unordered_map<std::string,PhaseCreator> phaseregistry_;
public:
    PEBFactory();
    void registerBehavior(const std::string& name,BehaviorCreator creator);
    void registerPhase(const std::string& name,PhaseCreator creator);
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    std::unique_ptr<Phase> createPhase(const sol::table& phasescript);
    std::unique_ptr<Enemy> createEnemy(const sol::table& enemyscript);
    std::unique_ptr<Behavior> createBehavior(Enemy* enemy,const sol::table& behaviorscript);
    //std::unique_ptr<Behavior> createBehavior(const sol::table& behaviorscript);
};

class BFactory
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;

public:
    using BehaviorCreator=std::function<std::unique_ptr<Behavior>(Enemy*,const sol::table&)>;
private:
    std::unordered_map<std::string,BehaviorCreator> behaviorregistry_;
public:
    BFactory();
    void registerBehavior(const std::string& name,BehaviorCreator creator);
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    std::unique_ptr<Behavior> buildBehavior(Enemy* enemy,const sol::table& behaviorscript);
}; 

class EFactory
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;
    BFactory Bfactory_;

public:
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    std::unique_ptr<Enemy> buildEnemy(const sol::table& enemyscript);
};

class PFactory
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;
    EFactory Efactory_;

public:
    using PhaseCreator=std::function<std::unique_ptr<Phase>(const sol::table& phasescript)>;
private:
    std::unordered_map<std::string,PhaseCreator> phaseregistry_;
public:
    PFactory();
    void registerPhase(const std::string& name,PhaseCreator creator);
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    std::unique_ptr<Phase> buildPhase(const sol::table& phasescript);
};

class ScriptLoader
{
private:
    LuaManager& lua_;
    Resource* resource_;
    YellowPage* yellowpage_;
    PEBFactory PEBfactory_;
    PFactory Pfactory_;

public:
    using PhaseCreator=std::function<std::unique_ptr<Phase>(const sol::table&)>;
private:
    std::unordered_map<std::string,PhaseCreator> phaseregistry_;
private:
    std::unique_ptr<Phase> buildPhase(const sol::table& phasescript);
    std::unique_ptr<Enemy> buildEnemy(const sol::table& enemyscript);
    std::unique_ptr<Behavior> buildBehavior(Enemy* enemy,const sol::table& behaviorscript);

public:
    ScriptLoader(LuaManager& lua);
    void registerPhase(const std::string& name,PhaseCreator creator);
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    void loadPhase(const std::string& path);
}; 