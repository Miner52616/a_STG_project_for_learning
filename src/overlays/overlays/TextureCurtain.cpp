#include "overlays/overlays/TextureCurtain.h"

TextureCurtain::TextureCurtain(sf::Texture& texture):
    finish_(false),enable_(false),texture_(&texture)
{
    vertices_=sf::VertexArray(sf::PrimitiveType::Triangles);
    sf::RenderStates state;
    state.texture=&texture;
    states_=state;
}

TextureCurtain::TextureCurtain(sf::Texture& texture,sf::Shader& shader):
    finish_(false),enable_(false),texture_(&texture)
{
    vertices_=sf::VertexArray(sf::PrimitiveType::Triangles);
    sf::RenderStates state;
    state.texture=&texture;
    state.shader=&shader;
    states_=state;
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