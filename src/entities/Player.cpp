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
    hitbox_texture_(resource->app_.hitboxTexture_),
    hitbox_exist_(false),
    a_low_(3),
    a_high_(4.5),
    a_(4.5),
    v_low_(3.5),
    v_high_(8),
    speed_x_(0),
    speed_y_(0),
    v_limit_(0),
    grazebox_r(50),
    request_shoot_(false),
    shining_(false),
    clock_((long long int)2),
    life_clock_((long long int)240),
    bomb_clock_((long long int)180),
    shining_clock_(2),
    outline_(outline),
    resource_(resource),
    //bulletconfig_(resource_->app_.bulletTexture_)
    life_(3),
    bomb_(3),
    power_(0)
{
    //std::cout<<"0"<<std::endl;
    point_.setRadius(6);
    point_.setOrigin(point_.getGlobalBounds().getCenter());
    point_.setFillColor(sf::Color::White);
    
    hitbox_texture_.setOrigin(hitbox_texture_.getGlobalBounds().getCenter());
    hitbox_texture_.setScale({2,2});

    hitbox_r_=1;
    hitbox_.setRadius(hitbox_r_);
    //std::cout<<"1"<<std::endl;
    setBulletConfig();
    setEffectConfig();
    setBombConfig();
    setOverlayConfig();
    //std::cout<<"2"<<std::endl;
    for(int i=1;i<=4;i++)
    {
        std::unique_ptr<Child_Plane> child_plane1=std::make_unique<Child_Plane>(resource_->app_.child_planeTexture_);
        child_plane1->setResource(resource_,this);
        child_plane1->setBulletConfig();
        child_plane1->setEffectConfig();
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
    bulletconfig_=std::make_shared<BulletConfig>(resource_->app_.playersheetTexture_);
    bulletconfig_->bullet_index_={1,1};
    bulletconfig_->damage_=4;
    bulletconfig_->bulletclass_=BulletClasses::PlayerBullet;
    bulletconfig_->r_=10;
    bulletconfig_->v_=50;
    bulletconfig_->spawn_point_=getPosition();
    bulletconfig_->color_alpha_=192;
}

void Player::setEffectConfig()
{
    effectconfig_=std::make_unique<EffectConfig>(resource_->app_.playersheetTexture_);
    effectconfig_->effect_index_={1,1};
    effectconfig_->effecttype_=PlayerBullet_Air;
    effectconfig_->random_rotate_=false;
    effectconfig_->texturelist_size_=4;
    effectconfig_->current_texture_num_=0;
    effectconfig_->time_=16;
    effectconfig_->v_=1.2;
    effectconfig_->direction_={0,-1};
    effectconfig_->color_alpha_=192;
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

void Player::setContinued(bool continued)
{
    continued_=continued;
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
    missed_=true;

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
    hitbox_texture_.setPosition(position_);
    picture_.setPosition(position_);
}

void Player::setPosition(sf::Vector2f position)
{
    position_=position;
    setPosition();
}

bool Player::isContinued()
{
    return continued_;
}

bool Player::isMissed()
{
    return missed_;
}

void Player::setMissed(bool missed)
{
    missed_=missed;
}

int Player::getLifeNum()
{
    return life_;
}

void Player::setLifeNum(int life)
{
    life_=life;
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
    if((life_>=0)&&(life_clock_.get_condition()))
    {
        resource_->bulletmanager_.clear_common_enemybullet();
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
        //texture.draw(point_);
        texture.draw(hitbox_texture_);
    }
}

void Player::Player_update()
{
    store_position();
    power_=yellowpage_->power_line_.getCurrentNum();
    
    if(life_clock_.get_condition())
    {
        picture_.setColor({255,255,255,255});
    }
    else
    {
        if(shining_clock_.get_condition())
        {
            if(shining_)
            {
                shining_=false;
                picture_.setColor({255,255,255,255});
            }
            else
            {
                shining_=true;
                picture_.setColor({255,255,255,127});
            }
        }
    }

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
            child_planes_[0]->setTargetPosition(sf::Vector2f{0,50});
            child_planes_[0]->setBulletDirection({0,-1});
            child_planes_[1]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 2:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-30,40});
            child_planes_[0]->setBulletDirection({-0.5,-0.866});
            child_planes_[1]->setTargetPosition(sf::Vector2f{30,40});
            child_planes_[1]->setBulletDirection({0.5,-0.866});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 3:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-40,30});
            child_planes_[0]->setBulletDirection({-0.5,-0.866});
            child_planes_[1]->setTargetPosition(sf::Vector2f{40,30});
            child_planes_[1]->setBulletDirection({0.5,-0.866});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,50});
            child_planes_[2]->setBulletDirection({0,-1});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 4:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-40,30});
            child_planes_[0]->setBulletDirection({-0.5,-0.866});
            child_planes_[1]->setTargetPosition(sf::Vector2f{40,30});
            child_planes_[1]->setBulletDirection({0.5,-0.866});
            child_planes_[2]->setTargetPosition(sf::Vector2f{-15.12,47.65});
            child_planes_[2]->setBulletDirection({-0.259,-0.96});
            child_planes_[3]->setTargetPosition(sf::Vector2f{15.12,47.65});
            child_planes_[3]->setBulletDirection({0.259,-0.96});
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
        v_limit_=v_low_;
        a_=a_low_;
    }
    else
    {
        hitbox_exist_=false;
        child_planes_[0]->setBulletDirection({0,-1});
        child_planes_[1]->setBulletDirection({0,-1});
        child_planes_[2]->setBulletDirection({0,-1});
        child_planes_[3]->setBulletDirection({0,-1});
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
            child_planes_[0]->setTargetPosition(sf::Vector2f{-40,-80});
            child_planes_[1]->setTargetPosition(sf::Vector2f{40,-80});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,0});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 3:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-50,-60});
            child_planes_[1]->setTargetPosition(sf::Vector2f{50,-60});
            child_planes_[2]->setTargetPosition(sf::Vector2f{0,-80});
            child_planes_[3]->setTargetPosition(sf::Vector2f{0,0});
            break;

        case 4:
            child_planes_[0]->setTargetPosition(sf::Vector2f{-50,-60});
            child_planes_[1]->setTargetPosition(sf::Vector2f{50,-60});
            child_planes_[2]->setTargetPosition(sf::Vector2f{-15,-80});
            child_planes_[3]->setTargetPosition(sf::Vector2f{15,-80});
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
        v_limit_=v_high_;
        a_=a_high_;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
    {
        if(speed_x_<v_limit_*0.707)
        {
            speed_x_=speed_x_+a_;
            if(speed_x_>v_limit_*0.707)
            {
                speed_x_=v_limit_*0.707;
            }
        }
        if(speed_x_>v_limit_*0.707)
        {
            speed_x_=speed_x_-a_high_;
            if(speed_x_<v_limit_*0.707)
            {
                speed_x_=v_limit_*0.707;
            }
        }
        if(speed_y_<v_limit_*0.707)
        {
            speed_y_=speed_y_+a_;
            if(speed_y_>v_limit_*0.707)
            {
                speed_y_=v_limit_*0.707;
            }
        }
        if(speed_y_>v_limit_*0.707)
        {
            speed_y_=speed_y_-a_high_;
            if(speed_y_<v_limit_*0.707)
            {
                speed_y_=v_limit_*0.707;
            }
        }
        setPosition({getPosition().x-speed_x_,getPosition().y-speed_y_});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
    {
        if(speed_x_<v_limit_*0.707)
        {
            speed_x_=speed_x_+a_;
            if(speed_x_>v_limit_*0.707)
            {
                speed_x_=v_limit_*0.707;
            }
        }
        if(speed_x_>v_limit_*0.707)
        {
            speed_x_=speed_x_-a_high_;
            if(speed_x_<v_limit_*0.707)
            {
                speed_x_=v_limit_*0.707;
            }
        }
        if(speed_y_<v_limit_*0.707)
        {
            speed_y_=speed_y_+a_;
            if(speed_y_>v_limit_*0.707)
            {
                speed_y_=v_limit_*0.707;
            }
        }
        if(speed_y_>v_limit_*0.707)
        {
            speed_y_=speed_y_-a_high_;
            if(speed_y_<v_limit_*0.707)
            {
                speed_y_=v_limit_*0.707;
            }
        }
        setPosition({getPosition().x-speed_x_,getPosition().y+speed_y_});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
    {
        if(speed_x_<v_limit_*0.707)
        {
            speed_x_=speed_x_+a_;
            if(speed_x_>v_limit_*0.707)
            {
                speed_x_=v_limit_*0.707;
            }
        }
        if(speed_x_>v_limit_*0.707)
        {
            speed_x_=speed_x_-a_high_;
            if(speed_x_<v_limit_*0.707)
            {
                speed_x_=v_limit_*0.707;
            }
        }
        if(speed_y_<v_limit_*0.707)
        {
            speed_y_=speed_y_+a_;
            if(speed_y_>v_limit_*0.707)
            {
                speed_y_=v_limit_*0.707;
            }
        }
        if(speed_y_>v_limit_*0.707)
        {
            speed_y_=speed_y_-a_high_;
            if(speed_y_<v_limit_*0.707)
            {
                speed_y_=v_limit_*0.707;
            }
        }
        setPosition({getPosition().x+speed_x_,getPosition().y-speed_y_});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
    {
        if(speed_x_<v_limit_*0.707)
        {
            speed_x_=speed_x_+a_;
            if(speed_x_>v_limit_*0.707)
            {
                speed_x_=v_limit_*0.707;
            }
        }
        if(speed_x_>v_limit_*0.707)
        {
            speed_x_=speed_x_-a_high_;
            if(speed_x_<v_limit_*0.707)
            {
                speed_x_=v_limit_*0.707;
            }
        }
        if(speed_y_<v_limit_*0.707)
        {
            speed_y_=speed_y_+a_;
            if(speed_y_>v_limit_*0.707)
            {
                speed_y_=v_limit_*0.707;
            }
        }
        if(speed_y_>v_limit_*0.707)
        {
            speed_y_=speed_y_-a_high_;
            if(speed_y_<v_limit_*0.707)
            {
                speed_y_=v_limit_*0.707;
            }
        }
        setPosition({getPosition().x+speed_x_,getPosition().y+speed_y_});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        if(speed_x_>0)
        {
            speed_x_=speed_x_-a_high_;
            if(speed_x_<0)
            {
                speed_x_=0;
            }
        }
        if(speed_y_<v_limit_)
        {
            speed_y_=speed_y_+a_;
            if(speed_y_>v_limit_)
            {
                speed_y_=v_limit_;
            }
        }
        if(speed_y_>v_limit_)
        {
            speed_y_=speed_y_-a_high_;
            if(speed_y_<v_limit_)
            {
                speed_y_=v_limit_;
            }
        }
        setPosition({position_.x,(position_.y)-speed_y_});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        if(speed_x_>0)
        {
            speed_x_=speed_x_-a_high_;
            if(speed_x_<0)
            {
                speed_x_=0;
            }
        }
        if(speed_y_<v_limit_)
        {
            speed_y_=speed_y_+a_;
            if(speed_y_>v_limit_)
            {
                speed_y_=v_limit_;
            }
        }
        if(speed_y_>v_limit_)
        {
            speed_y_=speed_y_-a_high_;
            if(speed_y_<v_limit_)
            {
                speed_y_=v_limit_;
            }
        }
        setPosition({position_.x,(position_.y)+speed_y_});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if(speed_y_>0)
        {
            speed_y_=speed_y_-a_high_;
            if(speed_y_<0)
            {
                speed_y_=0;
            }
        }
        if(speed_x_<v_limit_)
        {
            speed_x_=speed_x_+a_;
            if(speed_x_>v_limit_)
            {
                speed_x_=v_limit_;
            }
        }
        if(speed_x_>v_limit_)
        {
            speed_x_=speed_x_-a_high_;
            if(speed_x_<v_limit_)
            {
                speed_x_=v_limit_;
            }
        }
        setPosition({position_.x-speed_x_,position_.y});
        check_position();
    }
    else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if(speed_y_>0)
        {
            speed_y_=speed_y_-a_high_;
            if(speed_y_<0)
            {
                speed_y_=0;
            }
        }
        if(speed_x_<v_limit_)
        {
            speed_x_=speed_x_+a_;
            if(speed_x_>v_limit_)
            {
                speed_x_=v_limit_;
            }
        }
        if(speed_x_>v_limit_)
        {
            speed_x_=speed_x_-a_high_;
            if(speed_x_<v_limit_)
            {
                speed_x_=v_limit_;
            }
        }
        setPosition({position_.x+speed_x_,position_.y});
        check_position();
    }
    else
    {
        if(speed_x_>0)
        {
            speed_x_=speed_x_-a_high_;
            if(speed_x_<0)
            {
                speed_x_=0;
            }
        }
        if(speed_y_>0)
        {
            speed_y_=speed_y_-a_high_;
            if(speed_y_<0)
            {
                speed_y_=0;
            }
        }
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        if(clock_.get_condition())
        {
            //request_shoot_=true;
            //std::cout<<"shoot"<<std::endl;
            //resource_->bulletmanager_.add_process(std::make_unique<PlayerBullet>(resource_->app_.bulletTexture_,getPosition()));
            bulletconfig_->spawn_point_=getPosition()+sf::Vector2f{10,0};
            resource_->bulletmanager_.add_process(bulletconfig_.get(),effectconfig_.get());
            bulletconfig_->spawn_point_=getPosition()+sf::Vector2f{-10,0};
            resource_->bulletmanager_.add_process(bulletconfig_.get(),effectconfig_.get());


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
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        bulletconfig_->damage_=1.5;
        bulletconfig_->bulletclass_=BulletClasses::PlayerAimBullet;
        bulletconfig_->r_=10;
        bulletconfig_->v_=10;
        bulletconfig_->spawn_point_=getPosition();
        bulletconfig_->bullet_index_={1,11};
        bulletconfig_->bulletbehavior_=Direct;

        effectconfig_->effect_index_={1,2};
        effectconfig_->v_=0;
    }
    else
    {
        bulletconfig_->damage_=2;
        bulletconfig_->bulletclass_=BulletClasses::PlayerBullet;
        bulletconfig_->r_=10;
        bulletconfig_->v_=70;
        bulletconfig_->spawn_point_=getPosition();
        bulletconfig_->bullet_index_={9,1};
        bulletconfig_->bulletbehavior_=Fix;

        effectconfig_->effect_index_={9,2};
        effectconfig_->v_=1;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        if(clock_.get_condition())
        {
            //request_shoot_=true;
            //std::cout<<"shoot"<<std::endl;
            //resource_->bulletmanager_.add_process(std::make_unique<PlayerBullet>(resource_->app_.bulletTexture_,getPosition()));
            bulletconfig_->spawn_point_=getPosition();
            resource_->bulletmanager_.add_process(bulletconfig_.get(),effectconfig_.get());

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

void Child_Plane::setBulletDirection(sf::Vector2f direction)
{
    bulletconfig_->direction_=direction;
}

void Child_Plane::setBulletConfig()
{
    bulletconfig_=std::make_shared<BulletConfig>(resource_->app_.playersheetTexture_);
    bulletconfig_->damage_=8;
    bulletconfig_->bulletclass_=BulletClasses::PlayerAimBullet;
    bulletconfig_->color_alpha_=127;
    bulletconfig_->r_=10;
    bulletconfig_->v_=10;
    bulletconfig_->a_=0.5;
    bulletconfig_->spawn_point_=getPosition();
}

void Child_Plane::setEffectConfig()
{
    effectconfig_=std::make_unique<EffectConfig>(resource_->app_.playersheetTexture_);
    effectconfig_->effect_index_={9,2};
    effectconfig_->v_=1;
    effectconfig_->direction_={0,-1};
    effectconfig_->color_alpha_=192;
    effectconfig_->effecttype_=PlayerBullet_Air;
    effectconfig_->random_rotate_=false;
    effectconfig_->texturelist_size_=4;
    effectconfig_->current_texture_num_=0;
    effectconfig_->time_=16;
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