#pragma once
#include <SFML/Graphics.hpp>

class Application;

class Switch
{
private:
    Application& app_;

    sf::Vector2f position_;

    bool state_;
    //sf::Text text_;
    sf::RectangleShape frame_;
    sf::RectangleShape background_;
    sf::RectangleShape point_;

    bool last_mouse_state_;
    sf::Vector2f target_position_;
    sf::Vector3f current_RGB_;
    sf::Vector3f target_RGB_;

    sf::RenderTexture switch_texture;
    sf::Sprite switch_sprite_;
    //sf::RenderStates switch_render_state_;

public:
    Switch(Application& app);
    void update();
    void render(sf::RenderWindow& window);
    void setScale(sf::Vector2f scale);
    void setState(bool state);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    //void setSwitchText(const std::string& text);
    bool getState();
    //sf::Text& getText();
    //sf::Shape* getBackground();
    sf::Sprite& getSprite();
    bool isCursorInBounds();

    void applyChange();
};