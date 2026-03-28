#include "overlays/overlays/PictureOverlay.h"
#include "mathematics/mathematics.h"

PictureOverlay::PictureOverlay(const sf::Texture& texture):
    texture_(texture),picture_(texture_),position_({0,0})
{
    picture_.setOrigin(picture_.getGlobalBounds().getCenter());
    sf::Color color=picture_.getColor();
    color.a=128;
    picture_.setColor(color);
}

void PictureOverlay::update()
{
    sf::Vector2f  vec=center_position_-position_;
    if(vec.length()<=100)
    {
        setPosition(position_+v2_*direction_);
    }
    else
    {
        setPosition(position_+v1_*direction_);
    }
    
    if((targetposition_-position_).x*direction_.x<=0)
    {
        markDead();
    }
}

void PictureOverlay::render(sf::RenderWindow& window)
{
    window.draw(picture_);
}

void PictureOverlay::render(sf::RenderTexture& texture)
{
    texture.draw(picture_);
}

sf::Vector2f PictureOverlay::getPosition()
{
    return position_;
}

void PictureOverlay::setPosition(sf::Vector2f position)
{
    position_=position;
    picture_.setPosition(position_);
}

void PictureOverlay::setTargetPosition(sf::Vector2f position)
{
    targetposition_=position;
    direction_=normalize(targetposition_-position_);
    center_position_=(float)0.5*(targetposition_+position_);
}

void PictureOverlay::setV(float v1,float v2)
{
    v1_=v1;
    v2_=v2;
}