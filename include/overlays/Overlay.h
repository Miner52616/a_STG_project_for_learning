#pragma  once
#include <SFML/Graphics.hpp>
#include "behaviors/Behavior.h"

class Overlay
{
protected:
    std::shared_ptr<Behavior> behavior_;

public:
    Overlay(){;}
    void setBehavior(std::shared_ptr<Behavior> behavior);
    virtual void update()=0;
    virtual void render(sf::RenderWindow& window)=0;
};