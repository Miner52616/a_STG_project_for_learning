#include "entities/Player.h"
#include "core/application.h"
#include "ui/Frame.h"
#include "bullets/PlayerBullet.h"
#include "manager/BulletManager.h"

Player::Player(application &app,const sf::Texture &texture,Frame &outline,BulletManager& bulletmanager):
    Entity(app,texture),
    hitbox_exist_(false),
    speed_(10),
    request_shoot_(false),
    clock_((long long int)15),
    outline_(outline),
    bulletmanager_(bulletmanager)
{
    ;
}

void Player::check_position()
{
    if(getPosition().x<outline_.getGlobalBounds().position.x+20)
    {
        setPosition({outline_.getGlobalBounds().position.x+20,getPosition().y});
    }
    if(getPosition().y<outline_.getGlobalBounds().position.y+35)
    {
        setPosition({getPosition().x,outline_.getGlobalBounds().position.y+35});
    }
    if(getPosition().x>outline_.getGlobalBounds().position.x+outline_.getGlobalBounds().size.x-20)
    {
        setPosition({outline_.getGlobalBounds().position.x+outline_.getGlobalBounds().size.x-20,getPosition().y});
    }
    if(getPosition().y>outline_.getGlobalBounds().position.y+outline_.getGlobalBounds().size.y-35)
    {
        setPosition({getPosition().x,outline_.getGlobalBounds().position.y+outline_.getGlobalBounds().size.y-35});
    }
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
        check_position();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        setPosition({position_.x,(position_.y)+speed_});
        check_position();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        setPosition({position_.x-speed_,position_.y});
        check_position();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        setPosition({position_.x+speed_,position_.y});
        check_position();
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
        if(clock_.get_condition())
        {
            request_shoot_=true;
            bulletmanager_.add_process(std::make_unique<PlayerBullet>(app_,app_.bulletTexture_,getPosition(),outline_));
            clock_.reset();
        }
    }
}