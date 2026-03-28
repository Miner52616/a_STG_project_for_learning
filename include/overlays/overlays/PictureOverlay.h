#pragma once
#include "overlays/Overlay.h"

class PictureOverlay:public Overlay
{
protected:
    const sf::Texture& texture_;
    sf::Sprite picture_;
    sf::Vector2f position_;
    sf::Vector2f targetposition_;

    sf::Vector2f direction_;
    sf::Vector2f center_position_;
    float v1_;
    float v2_;

public:
    PictureOverlay(const sf::Texture& texture);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void render(sf::RenderTexture& texture) override;

    sf::Vector2f getPosition() override;
    void setPosition(sf::Vector2f position) override;
    void setTargetPosition(sf::Vector2f position);
    void setV(float v1,float v2);
};