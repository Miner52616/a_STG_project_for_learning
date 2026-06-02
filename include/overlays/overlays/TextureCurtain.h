#pragma once
#include <SFML/Graphics.hpp>

class TextureCurtain
{
protected:
    sf::VertexArray vertices_;
    sf::RenderStates states_;
    sf::Texture* texture_;
    bool finish_;
    bool enable_;

public:
    TextureCurtain(sf::Texture& texture);
    void setTexture(sf::Texture& texture);
    void setEnable(bool enable);
    bool isFinished();
    virtual void update()=0;
    virtual void render(sf::RenderWindow& window);
};