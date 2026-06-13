#pragma once
#include <SFML/Graphics.hpp>
#include "core/Clock.h"

class TextureCurtain
{
protected:
    sf::VertexArray vertices_;
    sf::RenderStates states_;
    const sf::Texture* texture_;
    bool have_fliped_;
    Clock delay_time_;

    bool finish_;
    bool enable_;
    bool flip_;

public:
    TextureCurtain(const sf::Texture& texture);
    TextureCurtain(const sf::Texture& texture,sf::Shader& shader);
    void setTexture(const sf::Texture& texture);
    void setEnable(bool enable);
    void setFlip(bool flip);
    void setDelayTime(long long int delay);
    bool isFinished();
    virtual void update()=0;
    virtual void render(sf::RenderWindow& window);
};