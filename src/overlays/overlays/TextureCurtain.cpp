#include "overlays/overlays/TextureCurtain.h"

TextureCurtain::TextureCurtain(sf::Texture& texture):
    finish_(false),enable_(false),texture_(&texture)
{
    vertices_=sf::VertexArray(sf::PrimitiveType::Triangles);
    states_.texture=&texture;
}

void TextureCurtain::setTexture(sf::Texture& texture)
{
    texture_=&texture;
    states_.texture=&texture;
}

void TextureCurtain::setEnable(bool enable)
{
    enable_=enable;
}

bool TextureCurtain::isFinished()
{
    return finish_;
}

void TextureCurtain::render(sf::RenderWindow& window)
{
    window.draw(vertices_,states_);
}