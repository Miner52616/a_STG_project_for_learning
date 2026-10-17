#pragma once
#include <SFML/Graphics.hpp>
#include "behaviors/Behavior.h"
#include "packages/EffectConfig.h"
#include "packages/Resource.h"
#include "core/Clock.h"
#include "ui/Text.h"
#include <memory>
#include <vector>

class EffectUpdateTableLibrary;

//特效
class Effect
{
friend EffectUpdateTableLibrary;

protected:
    //Resource* resource_;
    sf::Font* font_;
    sf::Texture* texture_;
    sf::Vector2f position_;
    sf::Vector2f prev_position_;
    bool dead_;
    bool active_;
    EffectConfig effectconfig_;

    Clock clock_;
    Clock texture_clock_;

    sf::Sprite picture_;
    Text text_;
    //std::vector<std::unique_ptr<Behavior>> behaviorlist_;

public:
    Effect(sf::Texture &texture,sf::Font &font);
    Effect(sf::Texture &texture,sf::Font &font,sf::Vector2f position,long long int time);

    virtual void setPosition(sf::Vector2f position);  //设置实体位置
    void store_position();
    sf::Vector2f getPosition();  //获得实体位置
    sf::Vector2f getprevPosition();
    //void setResource(Resource* resource);
    void setTime(long long int time);
    virtual bool isDead() const;
    void markDead();
    //void addBehavior(std::unique_ptr<Behavior> behavior);

    void setDead(bool dead);
    void initialize();
    void setActive(bool active);
    void rebuild();
    //void rebuild(sf::Texture &texture,sf::Vector2f position);
    //void rebuild_initialize();
    EffectConfig* getEffectConfig();

    virtual void update();
    virtual void drawwindow(sf::RenderWindow& window);  //渲染实体至屏幕
    virtual void drawtexture(sf::RenderTexture& texture);
};

class EffectUpdateTableLibrary
{
public:
    //static void direct_move1(Effect& effect);
    static void direct_move2(Effect& effect);
    static void keep_static(Effect& effect);
    static void keep_static2(Effect& effect);
    static void void_update(Effect& effect);
};

using EffectUpdateFunc=void(*)(Effect& effect);
extern EffectUpdateFunc effect_update_table[];