#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Button;

constexpr int row=7;
constexpr int column=13;
constexpr int max_input_length=10;

class KeyBoard
{
private:
    const sf::Font &font_;
    std::string origin_net_[row][column];
    std::vector<std::vector<Button>> key_net_;
    std::string input_;
    std::vector<int> focus_;
    sf::Vector2f position_;

public:
    KeyBoard(const sf::Font &font);
    void update();
    void render(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    std::vector<int> getFocus();
    void setFocus(const std::vector<int>& focus);
    std::string getString();
    void addString();
    void setString(std::string string);
};