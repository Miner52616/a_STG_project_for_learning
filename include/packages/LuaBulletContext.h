#pragma once
#include <SFML/Graphics.hpp>
#include <sol/sol.hpp>

class Entity;
class Resource;

class LuaBulletContext
{
private:
    //Lua绑定的实体与所需要的资源
    Entity* entity_;
    Resource* resource_;

public:
    //C++暴露给Lua的，弹幕描述所需要的接口
    sf::Vector2f getPosition();
    void spawnBullet(sol::table bulletconfig);    
    float random(float a,float b);

public:
    LuaBulletContext(Entity* entity,Resource* resource);
};