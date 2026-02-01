#include "entities/Player.h"

Player::Player(const sf::Texture &texture):
    Entity(texture),hitbox_exist_(false),speed_(10),request_shoot_(false),clock_((long long int)15)
{
    rate_.current=0;
    rate_.frame=15;
}

bool Player::Handle_shoot_request()
{
    if(request_shoot_)
    {
        request_shoot_=false;
        return true;
    }
    else
    {
        return false;
    }
}

void Player::clock_count()
{
    clock_.count();
}

void Player::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
    if(hitbox_exist_)
    {
        window.draw(hitbox_);
    }
}

void Player::Player_update()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        setPosition({position_.x,(position_.y)-speed_});
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        setPosition({position_.x,(position_.y)+speed_});
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        setPosition({position_.x-speed_,position_.y});
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        setPosition({position_.x+speed_,position_.y});
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        hitbox_exist_=true;
        speed_=5;
    }
    else
    {
        hitbox_exist_=false;
        speed_=15;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        /*
        rate_.current++;
        if(rate_.current>=rate_.frame)
        {
            request_shoot_=true;
            rate_.current=0;
        }
            */
        if(clock_.get_condition())
        {
            request_shoot_=true;
            clock_.reset();
        }
    }
}