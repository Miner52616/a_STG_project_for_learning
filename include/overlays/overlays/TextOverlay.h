#pragma once
#include "overlays/Overlay.h"
#include "ui/Text.h"

class TextOverlay:public Overlay
{
private:
    Text text_;
    sf::Vector2f position_;
    sf::Vector2f targetposition_;

public:
    TextOverlay(const sf::Font& font);
    void setTextText(const std::string text);
    void setTextSize(int size);  //设置文字大小
    void setTextColor(sf::Color color);  //设置文字颜色
    void changeOrigin(bool change);

    void render(sf::RenderWindow& window) override;
    void render(sf::RenderTexture& texture) override;
    sf::Vector2f getPosition() override;
    void setPosition(sf::Vector2f position) override;
};