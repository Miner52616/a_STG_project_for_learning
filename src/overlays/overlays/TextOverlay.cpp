#include "overlays/overlays/TextOverlay.h"

TextOverlay::TextOverlay(const sf::Font& font):
    text_(font)
{
    ;
}

void TextOverlay::setTextText(const std::string text)
{
    text_.setTextText(text);
}

void TextOverlay::setTextSize(int size)
{
    text_.setTextSize(size);
}

void TextOverlay::setTextColor(sf::Color color)
{
    text_.setTextColor(color);
}

void TextOverlay::render(sf::RenderWindow& window)
{
    text_.DrawText(window);
}

void TextOverlay::render(sf::RenderTexture& texture)
{
    text_.DrawText(texture);
}

sf::Vector2f TextOverlay::getPosition()
{
    return text_.getPosition();
}

void TextOverlay::setPosition(sf::Vector2f position)
{
    text_.setTextPosition(position);
}