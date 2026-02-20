#pragma once
#include <SFML/Graphics.hpp>

class application;

//实体，所有实体的基类
class Entity
{
protected:
    //application &app_;
    const sf::Texture &texture_;
    sf::Vector2f position_;
    sf::Vector2f prev_position_;
    int hitbox_r_;

protected:
    sf::CircleShape hitbox_;
    sf::Sprite picture_;

public:
    virtual void setPosition();
    virtual void setPosition(sf::Vector2f position);  //设置实体位置
    void store_position();
    sf::Vector2f getPosition();  //获得实体位置
    sf::Vector2f getprevPosition();
    int getHitbox_r();  //获得实体碰撞半径

    virtual void drawwindow(sf::RenderWindow& window);  //渲染实体至屏幕
    virtual void drawtexture(sf::RenderTexture& texture);

public:
    Entity(/*application &app,*/const sf::Texture &texture);  //初始化资源引用，默认实体设置
};