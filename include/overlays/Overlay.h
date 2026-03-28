#pragma  once
#include <SFML/Graphics.hpp>
#include "behaviors/Behavior.h"
#include <vector>
#include <memory>


class Overlay
{
protected:
    std::shared_ptr<Behavior> behavior_;
    std::vector<Behavior*> behaviorlist_;
    bool dead_;

public:
    Overlay();
    void setBehavior(std::shared_ptr<Behavior> behavior);
    void addBehavior(Behavior* behavior);
    virtual void update();
    virtual void render(sf::RenderWindow& window)=0;//{;};
    virtual void render(sf::RenderTexture& texture)=0;//{;};
    virtual sf::Vector2f getPosition()=0;
    virtual void setPosition(sf::Vector2f position)=0;
    void markDead();
    bool isDead();
};