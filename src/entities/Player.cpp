#include "entities/Player.h"
#include "core/application.h"
#include "ui/Frame.h"
#include "bullets/PlayerBullet.h"
#include "manager/BulletManager.h"

Player::Player(const sf::Texture &texture,Frame &outline,std::shared_ptr<Resource> resource):
    Entity(texture),
    hitbox_exist_(false),
    speed_(10),
    request_shoot_(false),
    clock_((long long int)15),
    outline_(outline),
    resource_(resource)
    //bulletconfig_(resource_->app_.bulletTexture_)
{
    std::cout<<"0"<<std::endl;
    point_.setRadius(6);
    point_.setOrigin(point_.getGlobalBounds().getCenter());
    point_.setFillColor(sf::Color::White);

    hitbox_r_=3;
    hitbox_.setRadius(hitbox_r_);
    std::cout<<"1"<<std::endl;
    /*
    bulletconfig_.damage_=100;
    bulletconfig_.bulletclass_=BulletClasses::PlayerBullet;
    bulletconfig_.r_=10;
    bulletconfig_.v_=10;
    bulletconfig_.spawn_point_=getPosition();*/
    std::cout<<"2"<<std::endl;
}

void Player::setBulletConfig()
{
    bulletconfig_=std::make_shared<BulletConfig>(resource_->app_.bulletTexture_);
    bulletconfig_->damage_=100;
    bulletconfig_->bulletclass_=BulletClasses::PlayerBullet;
    bulletconfig_->r_=10;
    bulletconfig_->v_=10;
    bulletconfig_->spawn_point_=getPosition();
}

void Player::check_position()
{
    /*
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
    }*/
    if(getPosition().x<20)
    {
        setPosition({20,getPosition().y});
    }
    if(getPosition().y<35)
    {
        setPosition({getPosition().x,35});
    }
    if(getPosition().x>770-20)
    {
        setPosition({770-20,getPosition().y});
    }
    if(getPosition().y>900-35)
    {
        setPosition({getPosition().x,900-35});
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

void Player::setResource(std::shared_ptr<Resource> resource)
{
    resource_=std::move(resource);
}

void Player::setPosition()
{
    hitbox_.setPosition(position_);
    point_.setPosition(position_);
    picture_.setPosition(position_);
}

void Player::setPosition(sf::Vector2f position)
{
    position_=position;
    setPosition();
}

void Player::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
    if(hitbox_exist_)
    {
        window.draw(point_);
    }
}

void Player::drawtexture(sf::RenderTexture& texture)
{
    texture.draw(picture_);
    if(hitbox_exist_)
    {
        texture.draw(point_);
    }
}

void Player::Player_update()
{
    store_position();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
    {
        setPosition({getPosition().x-(float)(speed_*0.707),getPosition().y-(float)(speed_*0.707)});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
    {
        setPosition({getPosition().x-(float)(speed_*0.707),getPosition().y+(float)(speed_*0.707)});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
    {
        setPosition({getPosition().x+(float)(speed_*0.707),getPosition().y-(float)(speed_*0.707)});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
    {
        setPosition({getPosition().x+(float)(speed_*0.707),getPosition().y+(float)(speed_*0.707)});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        setPosition({position_.x,(position_.y)-speed_});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        setPosition({position_.x,(position_.y)+speed_});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        setPosition({position_.x-speed_,position_.y});
        check_position();
    }
    else
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
        speed_=10;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        if(clock_.get_condition())
        {
            //request_shoot_=true;
            std::cout<<"shoot"<<std::endl;
            //resource_->bulletmanager_.add_process(std::make_unique<PlayerBullet>(resource_->app_.bulletTexture_,getPosition()));
            bulletconfig_->spawn_point_=getPosition();
            resource_->bulletmanager_.add_process(bulletconfig_);

            clock_.reset();
        }
    }
}