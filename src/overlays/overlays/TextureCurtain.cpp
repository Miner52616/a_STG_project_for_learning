#include "overlays/overlays/TextureCurtain.h"

TextureCurtain::TextureCurtain(const sf::Texture& texture):
    finish_(false),enable_(false),flip_(false),have_fliped_(false),delay_time_(0),
    texture_(&texture)
{
    vertices_=sf::VertexArray(sf::PrimitiveType::Triangles);
    sf::RenderStates state;
    state.texture=&texture;
    states_=state;
    delay_time_.reset();
}

TextureCurtain::TextureCurtain(const sf::Texture& texture,sf::Shader& shader):
    finish_(false),enable_(false),flip_(false),have_fliped_(false),delay_time_(0),
    texture_(&texture)
{
    vertices_=sf::VertexArray(sf::PrimitiveType::Triangles);
    sf::RenderStates state;
    state.texture=&texture;
    state.shader=&shader;
    states_=state;
    delay_time_.reset();
}

void TextureCurtain::setTexture(const sf::Texture& texture)
{
    texture_=&texture;
    states_.texture=&texture;
}

void TextureCurtain::setEnable(bool enable)
{
    enable_=enable;
}

void TextureCurtain::setFlip(bool flip)
{
    flip_=flip;
}

void TextureCurtain::setDelayTime(long long int delay)
{
    delay_time_.set_target(delay);
    delay_time_.reset();
}

bool TextureCurtain::isFinished()
{
    return finish_;
}

void TextureCurtain::render(sf::RenderWindow& window)
{
    if((flip_)&&(!have_fliped_))
    {
        have_fliped_=true;
        for(int i=1;i<=vertices_.getVertexCount();i++)
        {
            vertices_[i-1].texCoords={vertices_[i-1].texCoords.x,960-vertices_[i-1].texCoords.y};
        }
    }
    window.draw(vertices_,states_);
}