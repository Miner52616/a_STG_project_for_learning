#pragma once
#include "overlays/overlays/TextureCurtain.h"
#include "core/Clock.h"
#include <vector>

class MissCurtain:public TextureCurtain
{
private:
    std::vector<sf::CircleShape> circles_;
    sf::RenderTexture cache1_;
    sf::RenderTexture cache2_;
    sf::Sprite cache_sprite_;
    
    sf::Vector2f position_;
    Clock second_circle_;
    float expand_velocity_;

private:
    void initialize();
public:
    MissCurtain(sf::Texture& texture);
    MissCurtain(sf::Texture& texture,sf::Shader& shader);
    void reset();
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

    void update() override;
    void render(sf::RenderTexture& texture) override;
};