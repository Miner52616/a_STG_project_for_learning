#include "entities/Player.h"
#include "core/application.h"
#include "ui/Frame.h"
#include "ui/NumLine1.h"
#include "bullets/PlayerBullet.h"
#include "manager/BulletManager.h"
#include "manager/BombManager.h"
#include "manager/EffectManager.h"
#include "mathematics/mathematics.h"

Player::Player(const sf::Texture &texture,Frame &outline,Resource* resource):
    Entity(texture),
    hitbox_exist_(false),
    speed_(10),
    grazebox_r(50),
    request_shoot_(false),
    clock_((long long int)2),
    life_clock_((long long int)240),
    bomb_clock_((long long int)180),
    outline_(outline),
    resource_(resource),
    //bulletconfig_(resource_->app_.bulletTexture_)
    life_(2),
    bomb_(3),
    power_(0)
{
    std::cout<<"0"<<std::endl;
    point_.setRadius(6);
    point_.setOrigin(point_.getGlobalBounds().getCenter());
    point_.setFillColor(sf::Color::White);

    hitbox_r_=1;
    hitbox_.setRadius(hitbox_r_);
    std::cout<<"1"<<std::endl;
    setBulletConfig();
    setBombConfig();
    setOverlayConfig();
    std::cout<<"2"<<std::endl;
    for(int i=1;i<=4;i++)
    {
        std::unique_ptr<Child_Plane> child_plane1=std::make_unique<Child_Plane>(resource_->app_.child_planeTexture_);
        child_plane1->setResource(resource_,this);
        child_plane1->setBulletConfig();
        child_planes_.emplace_back(std::move(child_plane1));
    }
    /*
    std::unique_ptr<Child_Plane> child_plane1=std::make_unique<Child_Plane>(resource_->app_.child_planeTexture_);
    child_plane1->setResource(resource_,this);
    child_plane1->setBulletConfig();
    child_planes_.emplace_back(std::move(child_plane1));
    std::unique_ptr<Child_Plane> child_plane2=std::make_unique<Child_Plane>(resource_->app_.child_planeTexture_);
    child_plane2->setResource(resource_,this);
    child_plane2->setBulletConfig();
    child_planes_.emplace_back(std::move(child_plane2));
    */
}

void Player::setOverlayConfig()
{
    overlayconfig_=std::make_unique<OverlayConfig>(resource_->app_.overlay1Texture_);
    overlayconfig_->spawn_position_={970,650};
    overlayconfig_->target_position_={-200,250};
    overlayconfig_->v1_=12;
    overlayconfig_->v2_=5;
}

void Player::setBulletConfig()
{
    bulletconfig_=std::make_shared<BulletConfig>(resource_->app_.bulletTexture_);
    bulletconfig_->damage_=8;
    bulletconfig_->bulletclass_=BulletClasses::PlayerBullet;
    bulletconfig_->r_=10;
    bulletconfig_->v_=80;
    bulletconfig_->spawn_point_=getPosition();
}

void Player::setBombConfig()
{
    bombconfig_=std::make_unique<BombConfig>(resource_->app_.LeiTanTexture_);
    bombconfig_->bombtype_=BombType::LeiTan;
    bombconfig_->damage1_=2;
    bombconfig_->damage2_=120;
    bombconfig_->spawn_point_=getPosition();
    bombconfig_->direction_={350,0};
    bombconfig_->v_=6;
}

void Player::resetBombConfig()
{
    bombconfig_->bombtype_=BombType::LeiTan;
    bombconfig_->damage1_=2;
    bombconfig_->damage2_=120;
    bombconfig_->spawn_point_=getPosition();
    bombconfig_->direction_={350,0};
    bombconfig_->v_=6;
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

void Player::useBomb()
{
    if(bomb_>=1)
    {
        resource_->effectmanager_.add_process(overlayconfig_.get());
        bombconfig_->spawn_point_=getPosition()+bombconfig_->direction_;

        resource_->bombmanager_.add_process(bombconfig_.get());
        bombconfig_->direction_=round(bombconfig_->direction_,45);
        resource_->bombmanager_.add_process(bombconfig_.get());
        bombconfig_->direction_=round(bombconfig_->direction_,45);
        resource_->bombmanager_.add_process(bombconfig_.get());
        bombconfig_->direction_=round(bombconfig_->direction_,45);
        resource_->bombmanager_.add_process(bombconfig_.get());
        bombconfig_->direction_=round(bombconfig_->direction_,45);
        resource_->bombmanager_.add_process(bombconfig_.get());
        bombconfig_->direction_=round(bombconfig_->direction_,45);
        resource_->bombmanager_.add_process(bombconfig_.get());
        bombconfig_->direction_=round(bombconfig_->direction_,45);
        resource_->bombmanager_.add_process(bombconfig_.get());
        bombconfig_->direction_=round(bombconfig_->direction_,45);
        resource_->bombmanager_.add_process(bombconfig_.get());
        
        resetBombConfig();

        std::cout<<"use bomb"<<std::endl;
        bomb_--;
    }
}

void Player::clock_count()
{
    clock_.count();
    bomb_clock_.count();
    life_clock_.count();
    for(auto it=child_planes_.begin();it!=child_planes_.end();++it)
    {
        (*it)->clock_count();
    }
}

void Player::setResource(Resource* resource)
{
    resource_=resource;
}

void Player::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
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

int Player::getLifeNum()
{
    return life_;
}

int Player::getBombNum()
{
    return bomb_;
}

int Player::getGrazebox_r()
{
    return grazebox_r;
}

void Player::be_damage()
{
    if((life_>=1)&&(life_clock_.get_condition()))
    {
        life_--;
        if(bomb_<3)
        {
            bomb_=3;
        }
        setPosition({385,700});
        life_clock_.reset();
    }
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
    for(int i=1;i<=power_/100;i++)
    {
        child_planes_[i-1]->drawtexture(texture);
    }
    /*
    for(auto it=child_planes_.begin();it!=child_planes_.end();++it)
    {
        (*it)->drawtexture(texture);
    }
    */
    if(hitbox_exist_)
    {
        texture.draw(point_);
    }
}

void Player::Player_update()
{
    store_position();
    power_=yellowpage_->power_line_.getCurrentNum();
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

/*
    if(child_planes_[0]->getPosition()==sf::Vector2f{0,0})
    {
        child_planes_[0]->setPosition(prev_position_+sf::Vector2f{-80,0});
        child_planes_[1]->setPosition(prev_position_+sf::Vector2f{80,0});
    }
    
    child_planes_[0]->setPosition(child_planes_[0]->getPosition()+(getPosition()-prev_position_));
    child_planes_[1]->setPosition(child_planes_[1]->getPosition()+(getPosition()-prev_position_));
  */
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        hitbox_exist_=true;
        switch (power_/100)
        {
        case 0:
            child_planes_[0]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[1]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 1:
            child_planes_[0]->setTargetPosition(sf::Vector2f{0,100});
            child_planes_[1]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 2:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-60,80});
            child_planes_[1]->setTargetPosition(sf::Vector2f{60,80});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 3:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-70,70});
            child_planes_[1]->setTargetPosition(sf::Vector2f{70,70});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,100});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 4:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-80,60});
            child_planes_[1]->setTargetPosition(sf::Vector2f{80,60});
            child_planes_[2]->setTargetPosition(sf::Vector2f{-60,80});
            child_planes_[3]->setTargetPosition(sf::Vector2f{60,80});
            break;

        default:
            break;
        }
        /*
        child_planes_[0]->setTargetPosition(sf::Vector2f{-80,80});
        child_planes_[1]->setTargetPosition(sf::Vector2f{-30,100});
        child_planes_[2]->setTargetPosition(sf::Vector2f{30,100});
        child_planes_[3]->setTargetPosition(sf::Vector2f{80,80});
        */
        speed_=5;
    }
    else
    {
        hitbox_exist_=false;
        switch (power_/100)
        {
        case 0:
            child_planes_[0]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[1]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 1:
            child_planes_[0]->setTargetPosition(sf::Vector2f{0,-50});
            child_planes_[1]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 2:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-20,-50});
            child_planes_[1]->setTargetPosition(sf::Vector2f{20,-50});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 3:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-25,-50});
            child_planes_[1]->setTargetPosition(sf::Vector2f{25,-50});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,-50});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 4:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-30,-50});
            child_planes_[1]->setTargetPosition(sf::Vector2f{30,-50});
            child_planes_[2]->setTargetPosition(sf::Vector2f{-10,-50});
            child_planes_[3]->setTargetPosition(sf::Vector2f{10,-50});
            break;

        default:
            break;
        }
        /*
        child_planes_[0]->setTargetPosition(sf::Vector2f{-20,-50});
        child_planes_[1]->setTargetPosition(sf::Vector2f{-10,-50});
        child_planes_[2]->setTargetPosition(sf::Vector2f{10,-50});
        child_planes_[3]->setTargetPosition(sf::Vector2f{20,-50});
        */
        speed_=10;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        if(clock_.get_condition())
        {
            //request_shoot_=true;
            //std::cout<<"shoot"<<std::endl;
            //resource_->bulletmanager_.add_process(std::make_unique<PlayerBullet>(resource_->app_.bulletTexture_,getPosition()));
            bulletconfig_->spawn_point_=getPosition();
            resource_->bulletmanager_.add_process(bulletconfig_.get());

            clock_.reset();
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
    {
        if(bomb_clock_.get_condition())
        {
            useBomb();
            bomb_clock_.reset();
        }
    }

    int i=1;
    for(;i<=power_/100;i++)
    {
        child_planes_[i-1]->update();
    }
    for(;i<=4;i++)
    {
        child_planes_[i-1]->setRelativePosition({0,0});
    }
    /*
    //int i=1;
    for(auto it=child_planes_.begin();it!=child_planes_.end();++it)
    {
        //if(power_/100>=i)
        (*it)->update();
        //i++;
    }
        */
}

//********************************************************************
//********************************************************************
//********************************************************************

Child_Plane::Child_Plane(const sf::Texture &texture):
    Entity(texture),clock_((long long int)4),target_position_({0,0})
{
    ;
}

Child_Plane::Child_Plane(const sf::Texture &texture,Resource* resource,Player* player):
    Entity(texture),clock_((long long int)4),target_position_({0,0}),resource_(resource),player_(player)
{
    ;
}

void Child_Plane::update()
{
    store_position();
    //setPosition(getPosition()+(float)0.15*(target_position_-getPosition()));
    setRelativePosition(getRelativePosition()+(float)0.15*(target_position_-getRelativePosition()));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        if(clock_.get_condition())
        {
            //request_shoot_=true;
            //std::cout<<"shoot"<<std::endl;
            //resource_->bulletmanager_.add_process(std::make_unique<PlayerBullet>(resource_->app_.bulletTexture_,getPosition()));
            bulletconfig_->spawn_point_=getPosition();
            resource_->bulletmanager_.add_process(bulletconfig_.get());

            clock_.reset();
        }
    }
}

void Child_Plane::setPosition(sf::Vector2f position)
{
    position_=position;
    relative_position_=position-player_->getPosition();
    picture_.setPosition(position);
}

void Child_Plane::setRelativePosition(sf::Vector2f position)
{
    relative_position_=position;
    position_=player_->getPosition()+position;
    Entity::setPosition();
}

sf::Vector2f Child_Plane::getRelativePosition()
{
    return relative_position_;
}

void Child_Plane::setTargetPosition(sf::Vector2f target_position)
{
    target_position_=target_position;
}

void Child_Plane::setBulletConfig()
{
    bulletconfig_=std::make_shared<BulletConfig>(resource_->app_.bulletTexture_);
    bulletconfig_->damage_=8;
    bulletconfig_->bulletclass_=BulletClasses::PlayerBullet;
    bulletconfig_->r_=10;
    bulletconfig_->v_=10;
    bulletconfig_->spawn_point_=getPosition();
}

void Child_Plane::setResource(Resource* resource,Player* player)
{
    resource_=resource;
    player_=player;
}

void Child_Plane::clock_count()
{
    clock_.count();
}