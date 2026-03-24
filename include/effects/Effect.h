#pragma once
#include <SFML/Graphics.hpp>
#include "behaviors/Behavior.h"
#include "core/Clock.h"
#include <memory>
#include <vector>


//所有特效的基类！
class Effect
{
protected:
    const sf::Texture &texture_;
    sf::Vector2f position_;
    sf::Vector2f prev_position_;
    bool dead_;
    Clock clock_;

    sf::Sprite picture_;
    std::vector<std::unique_ptr<Behavior>> behaviorlist_;

public:
    Effect(const sf::Texture &texture);
    Effect(const sf::Texture &texture,sf::Vector2f position,long long int time);

    virtual void setPosition(sf::Vector2f position);  //设置实体位置
    void store_position();
    sf::Vector2f getPosition();  //获得实体位置
    sf::Vector2f getprevPosition();
    void setTime(long long int time);
    virtual bool isDead() const;
    void markDead();
    void addBehavior(std::unique_ptr<Behavior> behavior);

    virtual void update();
    virtual void drawwindow(sf::RenderWindow& window);  //渲染实体至屏幕
    virtual void drawtexture(sf::RenderTexture& texture);
};