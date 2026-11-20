#include "ui/Switch.h"
#include "core/Application.h"
#include "mathematics/mathematics.h"
#include <iostream>

Switch::Switch(Application& app):
    app_(app),
    state_(false),
    //text_(font_),
    frame_({150,90}),
    background_({140,80}),
    point_({70,70}),
    last_mouse_state_(false),
    target_position_({10,10}),
    current_RGB_({0,0,0}),
    target_RGB_({0,0,0}),
    switch_sprite_(switch_texture.getTexture())
{
    frame_.setPosition({0,0});
    frame_.setFillColor(sf::Color::White);
    background_.setPosition({5,5});
    background_.setFillColor(sf::Color::Black);
    point_.setPosition({10,10});
    point_.setFillColor(sf::Color::White);

    applyChange();

    switch_sprite_.setPosition({0,0});
    switch_sprite_.setScale({1,-1});
}

void Switch::update()
{
    bool curren_mouse_state=sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    if(isCursorInBounds())
    {
        if((last_mouse_state_==true)&&(curren_mouse_state==false))
        {
            switch (state_)
            {
            case false:
                {
                    state_=true;
                    break;
                }
            case true:
                {
                    state_=false;
                    break;
                }
            
            default:
                state_=false;
                break;
            }
        }       
    }

    switch (state_)
    {
    case false:
        {
            target_position_={10,10};
            target_RGB_={0,0,0};
            break;
        }
    case true:
        {
            target_position_={70,10};
            target_RGB_={0,255,0};
            break;
        }
    
    default:
        target_position_={10,10};
        target_RGB_={0,0,0};
        break;
    }
    
    float speed=0.08;
    current_RGB_=P_calculate<sf::Vector3f>(current_RGB_,target_RGB_,speed);
    background_.setFillColor(sf::Color(current_RGB_.x,current_RGB_.y,current_RGB_.z));
    point_.setPosition(P_calculate<sf::Vector2f>(point_.getPosition(),target_position_,speed));

    last_mouse_state_=curren_mouse_state;
}

void Switch::render(sf::RenderWindow& window)
{
    switch_texture.draw(frame_);
    switch_texture.draw(background_);
    switch_texture.draw(point_);
    switch_sprite_.setTexture(switch_texture.getTexture());

    window.draw(switch_sprite_);
}

void Switch::setScale(sf::Vector2f scale)
{
    switch_sprite_.setScale(scale);
}

void Switch::setState(bool state)
{
    state_=state;
}

void Switch::setPosition(sf::Vector2f position)
{
    //UI::setPosition(position);
    position_=position;
    switch_sprite_.setPosition(position);
}

sf::Vector2f Switch::getPosition()
{
    return position_;
}

/*
void Switch::setSwitchText(const std::string& text)
{
    text_.setString(sf::String::fromUtf8(text.begin(),text.end()));
}
    */

bool Switch::getState()
{
    return state_;
}

/*
sf::Text& Switch::getText()
{
    return text_;
}
    */

/*
sf::Shape* Switch::getBackground()
{
    return background_.get();
}
    */

sf::Sprite& Switch::getSprite()
{
    return switch_sprite_;
}

bool Switch::isCursorInBounds()
{
    sf::Vector2f bound=frame_.getLocalBounds().size;
    sf::Vector2f center=getPosition();
    sf::Vector2f cursor_position=app_.window_.mapPixelToCoords(sf::Mouse::getPosition(app_.window_));
    if((cursor_position.x<(center.x+0.5*bound.x))&&(cursor_position.x>(center.x-0.5*bound.x))&&(cursor_position.y<(center.y+0.5*bound.y))&&(cursor_position.y>(center.y-0.5*bound.y)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Switch::applyChange()
{
    switch_texture.resize({frame_.getLocalBounds().size.x,frame_.getLocalBounds().size.y});
    switch_sprite_.setTexture(switch_texture.getTexture(),true);
    switch_sprite_.setOrigin(switch_sprite_.getLocalBounds().getCenter());
}