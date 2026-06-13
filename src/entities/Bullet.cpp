#include "entities/Bullet.h"
#include "behaviors/Behavior.h"
#include "core/application.h"
#include "mathematics/mathematics.h"
#include "manager/PhaseController.h"
#include "manager/BulletManager.h"
#include <iostream>

Bullet::Bullet(sf::Texture &texture,sf::Vector2f position):
    Entity(texture),bullet_texture_(&texture),exist_(true),dead_(false),active_(false),grazed_(false),ofplayer_(true),damage_(100),
    effectconfig_(texture)
{
    bulletconfig_=std::make_unique<BulletConfig>(texture);
    //sonconfig_=std::make_unique<BulletConfig>(texture);
    position_=position;
    hitbox_r_=10;
    hitbox_draw_.setRadius(hitbox_r_);
    hitbox_draw_.setFillColor(sf::Color::Red);
    hitbox_draw_.setOrigin(hitbox_draw_.getLocalBounds().getCenter());
}

Bullet::Bullet(sf::Texture &texture,sf::Vector2f position,float damage):
    Entity(texture),bullet_texture_(&texture),exist_(true),dead_(false),active_(false),grazed_(false),ofplayer_(true),damage_(damage),
    effectconfig_(texture)
{
    bulletconfig_=std::make_unique<BulletConfig>(texture);
    //sonconfig_=std::make_unique<BulletConfig>(texture);
    position_=position;
    hitbox_r_=10;
    hitbox_draw_.setRadius(hitbox_r_);
    hitbox_draw_.setOrigin(hitbox_draw_.getLocalBounds().getCenter());
}

void Bullet::selfbehavior()
{
    switch (bulletconfig_->bulletbehavior_)
    {
    case BulletBehavior::Fix:
        {
            break;
        }
    
    case BulletBehavior::Rotate:
        {
            picture_.rotate(sf::degrees(3));
            break;
        }

    case BulletBehavior::Direct:
        {
            picture_.setRotation(sf::degrees(bulletconfig_->angle_));
            break;
        }
    
    default:
        break;
    }
}

void Bullet::update()
{
    store_position();
    
    //if(bulletconfig_->bulletclass_==DirectBullet2)
    //std::cout<<"111"<<std::endl;
    update_table[bulletconfig_->bulletclass_](*this,yellowpage_,resource_);
    //if(bulletconfig_->bulletclass_==DirectBullet2)
    //std::cout<<"222"<<std::endl;
    selfbehavior();
    //if(bulletconfig_->bulletclass_==DirectBullet2)
    //std::cout<<"333"<<std::endl;
    effectconfig_.spawn_point_=getPosition();
    //if(bulletconfig_->bulletclass_==DirectBullet2)
    //std::cout<<"444"<<std::endl;

    if(isOut())
    {
        //std::cout<<getPosition().x<<" "<<getPosition().y<<std::endl;
        markDead();
    }
    //if(bulletconfig_->bulletclass_==DirectBullet2)
    //std::cout<<"555"<<std::endl;
}

void Bullet::drawtexture(sf::RenderTexture& texture)
{
    texture.draw(picture_);
    if(show_hitbox_)
    {
        texture.draw(hitbox_draw_);
    }
}

void Bullet::setPosition(sf::Vector2f position)
{
    Entity::setPosition(position);
    hitbox_draw_.setPosition(position);
}

bool Bullet::isDead() const
{
    return dead_;
}

bool Bullet::isAcitve()
{
    return active_;
}

bool Bullet::isGrazed()
{
    return grazed_;
}

bool Bullet::isPlayer()
{
    return ofplayer_;
}

bool Bullet::isNotClear()
{
    return bulletconfig_->not_clear_;
}

bool Bullet::isOut()
{
    if(getPosition().x<=-100||getPosition().y<=-100||getPosition().x>=870||getPosition().y>=1000)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Bullet::rebuild(sf::Texture &texture,sf::Vector2f position)
{
    if(&texture!=bullet_texture_)
    {
        //std::cout<<"texture reset"<<std::endl;
        bullet_texture_=&texture;
        picture_.setTexture(*bullet_texture_,true);
    }
    rebuild_Initialize();
    picture_.setScale({1.414,1.414});
    picture_.setOrigin(picture_.getLocalBounds().getCenter());
    position_=position;
    hitbox_r_=bulletconfig_->r_;
    hitbox_draw_.setRadius(hitbox_r_);
    hitbox_draw_.setOrigin(hitbox_draw_.getLocalBounds().getCenter());
}

void Bullet::rebuild(sf::Texture &texture,sf::Vector2f position,float damage)
{
    if(&texture!=bullet_texture_)
    {
        //std::cout<<"texture reset"<<std::endl;
        bullet_texture_=&texture;
        picture_.setTexture(*bullet_texture_,true);
    }
    rebuild_Initialize();
    picture_.setScale({1.414,1.414});
    picture_.setOrigin(picture_.getLocalBounds().getCenter());
    damage_=damage;
    position_=position;
    hitbox_r_=bulletconfig_->r_;
    hitbox_draw_.setRadius(hitbox_r_);
    hitbox_draw_.setOrigin(hitbox_draw_.getLocalBounds().getCenter());
}

void Bullet::rebuild_Initialize()
{
    switch (bulletconfig_->bulletclass_)
    {
    case BulletClasses::PlayerBullet:
        {
            std::vector<int> rect=playersheet_bullet_transform(bulletconfig_->bullet_index_);
            sf::Vector2i position={rect[0],rect[1]};
            sf::Vector2i size={rect[2],rect[3]};
            picture_.setTextureRect({position,size});
            picture_.setRotation(sf::degrees(-90));

            //initialize_playerEffectConfig();
            break;
        }
    
    default:
        {
            switch (bulletconfig_->bulletsize_)
            {
            case BulletSize::Small:
                {
                    //std::cout<<"111"<<std::endl;
                    std::vector<int> rect=bulletsheet_transform(bulletconfig_->bullet_index_);
                    sf::Vector2i position={rect[0],rect[1]};
                    sf::Vector2i size={rect[2],rect[3]};
                    picture_.setTextureRect({position,size});
                    //picture_.setRotation(sf::degrees(90));

                    break;
                }

            case BulletSize::Big:
                {
                    std::vector<int> rect=big_bulletsheet_transform(bulletconfig_->bullet_index_);
                    sf::Vector2i position={rect[0],rect[1]};
                    sf::Vector2i size={rect[2],rect[3]};
                    picture_.setTextureRect({position,size});
                    //picture_.setRotation(sf::degrees(90));

                    break;
                }

            case BulletSize::Large:
                {
                    std::vector<int> rect=large_bulletsheet_transform(bulletconfig_->bullet_index_);
                    sf::Vector2i position={rect[0],rect[1]};
                    sf::Vector2i size={rect[2],rect[3]};
                    picture_.setTextureRect({position,size});
                    //picture_.setRotation(sf::degrees(90));

                    break;
                }
            
            default:
                break;
            }

            //initialize_EffectConfig();

            break;
        }
    }

    picture_.setColor(sf::Color{255,255,255,bulletconfig_->color_alpha_});
}

void Bullet::initialize()
{
    dead_=false;
    exist_=true;
    grazed_=false;
    ofplayer_=true;
}

void Bullet::setBulletConfig(std::unique_ptr<BulletConfig> bulletconfig)
{
    bulletconfig_=std::move(bulletconfig);
}

/*
//在自己被注入资源后调用（在BulletFactory中的setResource中被注入资源，在自己被注入资源的同时（被调用自己的setResource时）调用）
void Bullet::initialize_EffectConfig()
{
    
    std::vector<sf::Texture*> texturelist;
    texturelist.emplace_back(&resource_->app_.Air_1_1Texture_);
    texturelist.emplace_back(&resource_->app_.Air_1_2Texture_);
    texturelist.emplace_back(&resource_->app_.Air_1_3Texture_);
    texturelist.emplace_back(&resource_->app_.Air_1_4Texture_);
    texturelist.emplace_back(&resource_->app_.Air_1_5Texture_);
    texturelist.emplace_back(&resource_->app_.Air_1_6Texture_);
    texturelist.emplace_back(&resource_->app_.Air_1_7Texture_);
    texturelist.emplace_back(&resource_->app_.Air_1_8Texture_);
    effectconfig_.current_texture_num_=0;
    effectconfig_.texturelist_=texturelist;
    effectconfig_.effecttype_=EffectType::Bullet_Air;
    effectconfig_.texturelist_size_=texturelist.size();
    effectconfig_.time_=4*(effectconfig_.texturelist_size_-1);
    
}
*/
/*
void Bullet::initialize_playerEffectConfig()
{
    //effectconfig_.texturelist_.clear();
    effectconfig_.current_texture_num_=0;
    effectconfig_.effecttype_=EffectType::PlayerBullet_Air;
    effectconfig_.effect_index_={1,1};
    effectconfig_.texturelist_size_=4;
    effectconfig_.time_=4*(effectconfig_.texturelist_size_-1);
}
*/
/*
void Bullet::reset_EffectConfig()
{
    effectconfig_.current_texture_num_=0;
}
    */

BulletConfig* Bullet::getBulletConfig()
{
    return bulletconfig_.get();
}

EffectConfig* Bullet::getEffectConfig()
{
    return &effectconfig_;
}

void Bullet::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
}

void Bullet::setResource(Resource* resource)
{
    resource_=resource;
    sonconfig_=std::make_unique<BulletConfig>(resource->app_.bulletsheetTexture_);
    //initialize_EffectConfig();
}

void Bullet::setDead(bool dead)
{
    dead_=dead;
}

void Bullet::setHitbox_r(int r)
{
    hitbox_r_=r;
}

void Bullet::setbelong(bool ofplayer)
{
    ofplayer_=ofplayer;
}

void Bullet::markDead()
{
    dead_=true;
}

void Bullet::setActive(bool active)
{
    active_=active;
}

void Bullet::markGrazed()
{
    grazed_=true;
}

float Bullet::getDamage()
{
    return damage_;
}

/*
void Bullet::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
}
    */

//************************************************************** */
//以下是子弹移动函数表的移动函数实现

//子弹以 位置P控制 模式向目标position移动
//开销小，未使用开根号
//目前没有子弹使用这个移动函数
//使用配置v_ target_point_
void aim_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*(bullet.bulletconfig_->target_point_-bullet.getPosition()));
}

//子弹以定加速度大小，加速度方向指向离子弹最近敌人position来向目标敌人position移动
//有一定开销，使用了开根号
//自机的诱导弹使用这个移动函数
//使用配置a_
void aim_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    sf::Vector2f target=resource->phasecontroller_.get_closest_target(bullet.getPosition());
    if(target!=(sf::Vector2f{2500,2500}))
    {
        sf::Vector2f a_direction=target-bullet.getPosition();
        a_direction=bullet.bulletconfig_->a_*normalize(a_direction);
        sf::Vector2f direction=bullet.bulletconfig_->v_*bullet.bulletconfig_->direction_+a_direction;
        bullet.bulletconfig_->angle_=RadTransToDegree(atan2f(direction.y,direction.x));
        direction=normalize(direction);
        bullet.bulletconfig_->direction_=direction;
    }
    
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*bullet.bulletconfig_->direction_);
}

//子弹匀速直线移动
//开销很小
//使用配置v_ direction_
void direct_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*bullet.bulletconfig_->direction_);
}

//两个阶段的直线移动。第一阶段子弹以v_匀速直线移动，第二阶段在第一阶段基础上开始加速，加速至上限速度后匀速直线运动
//开销很小
//使用配置v_ a_ v2_ direction_ clock1_
void direct_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    if(!bullet.bulletconfig_->clock1_.get_condition())
    {
        bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
    }
    else
    {
        bullet.bulletconfig_->v_=bullet.bulletconfig_->v_+bullet.bulletconfig_->a_;
        if(bullet.bulletconfig_->v_>bullet.bulletconfig_->v2_)
        {
            bullet.bulletconfig_->v_=bullet.bulletconfig_->v2_;
        }
        bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
    }
    bullet.bulletconfig_->clock1_.count();
}

//四个阶段的直线运动。第一阶段子弹原地不动，第二阶段子弹加/减速直线运动，第三阶段匀速直线运动，第四阶段在第三阶段基础上加速直线运动，到最大速度后以最大速度匀速直线运动
//基本为NonSpell2特化使用
//有一定开销
//使用配置v_ v2_ v3_ a_ a2_ direction_ clock1_ clock2_ clock3_
void direct_move3(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    if(!bullet.bulletconfig_->clock3_.get_condition())
    {
        bullet.setPosition(bullet.getPosition());
        bullet.bulletconfig_->clock3_.count();
    }
    else
    {
        if(!bullet.bulletconfig_->clock2_.get_condition())
        {
            bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v3_*bullet.bulletconfig_->direction2_);
            //std::cout<<bullet.bulletconfig_->direction2_.x<<" "<<bullet.bulletconfig_->direction2_.y<<std::endl;
            bullet.bulletconfig_->v3_=bullet.bulletconfig_->v3_+bullet.bulletconfig_->a2_;
            bullet.bulletconfig_->clock2_.count();
        }
        else
        {
            if(!bullet.bulletconfig_->clock1_.get_condition())
            {
                bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
                bullet.bulletconfig_->clock1_.count();
            }
            else
            {
                bullet.bulletconfig_->v_=bullet.bulletconfig_->v_+bullet.bulletconfig_->a_;
                if(bullet.bulletconfig_->v_>bullet.bulletconfig_->v2_)
                {
                    bullet.bulletconfig_->v_=bullet.bulletconfig_->v2_;
                }
                bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
            }
        }
    }
}

//子弹会受到固定大小方向向下的加速度，同时子弹也有速度上限
//有一定开销
//使用配置v_ v2_  direction_（初速度方向） a_
void gravity_move(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*bullet.bulletconfig_->direction_);
    
    sf::Vector2f direction=bullet.bulletconfig_->v_*bullet.bulletconfig_->direction_;
    direction=direction+bullet.bulletconfig_->a_*sf::Vector2f{0,1};
    bullet.bulletconfig_->v_=direction.length();
    bullet.bulletconfig_->angle_=RadTransToDegree(atan2f(direction.y,direction.x))-90;
    bullet.bulletconfig_->direction_=normalize(direction);
    
    if((bullet.bulletconfig_->v_)>(bullet.bulletconfig_->v2_))
    {
        bullet.bulletconfig_->v_=bullet.bulletconfig_->v2_;
    }
}

//子弹从匀速移动，但每帧都移动方向都会旋转固定角度，直到旋转角度上限
//使用配置v_ direction_ rotate_angle_ rotate_angle2_
void rotate_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*bullet.bulletconfig_->direction_);

    if(bullet.bulletconfig_->rotate_angle2_>0)
    {
        bullet.bulletconfig_->direction_=roundwithCenter({0,0},bullet.bulletconfig_->direction_,bullet.bulletconfig_->rotate_angle_);
        bullet.bulletconfig_->rotate_angle2_=bullet.bulletconfig_->rotate_angle2_-abs(bullet.bulletconfig_->rotate_angle_);
        bullet.bulletconfig_->angle_=bullet.bulletconfig_->angle_+bullet.bulletconfig_->rotate_angle_;
    }
}

//子母弹。母弹匀速直线运动，每一定时间触发一次生成一波子弹。子弹生成方向随机
//母弹使用配置v_ direction_ clock1_ bullet_num_
//子弹使用配置v2_ r2_ bullet_index2_
void behavior_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*bullet.bulletconfig_->direction_);
    if(bullet.bulletconfig_->clock1_.get_condition())
    {
        bullet.bulletconfig_->clock1_.reset();
        //BulletConfig bullet.sonconfig_->(*(bullet.bullet_texture_));
        bullet.sonconfig_->spawn_point_=bullet.getPosition();
        bullet.sonconfig_->v_=bullet.bulletconfig_->v2_;
        bullet.sonconfig_->r_=bullet.bulletconfig_->r2_;
        bullet.sonconfig_->bullet_index_=bullet.bulletconfig_->bullet_index2_;
        //bullet.sonconfig_->.direction_=roundwithCenter({0,0},{1,0},bullet.bulletconfig_->angle2_);
        //bullet.sonconfig_->.angle_=bullet.bulletconfig_->angle2_;
        bullet.sonconfig_->bulletbehavior_=Direct;
        bullet.sonconfig_->bulletclass_=DirectBullet1;
        bullet.sonconfig_->bulletsize_=Small;

        for(int i=1;i<=bullet.bulletconfig_->bullet_num_;i++)
        {
            bullet.sonconfig_->angle_=bullet.bulletconfig_->angle2_+(i-1)*360/(bullet.bulletconfig_->bullet_num_);
            bullet.sonconfig_->direction_=roundwithCenter({0,0},{0,1},bullet.bulletconfig_->angle2_+(i-1)*360/(bullet.bulletconfig_->bullet_num_));
            resource->bulletmanager_.add_process(bullet.sonconfig_.get(),bullet.getEffectConfig());
        }
    }
    bullet.bulletconfig_->clock1_.count();
}

//需要有共享状态batch控制的多阶段多旋转中心旋转移动子弹。阶段由共享状态控制。第一阶段绕一个中心旋转指定的角度后停止，第二阶段绕第二个中心加速旋转至速度上限
//同时也是子母弹。在共享状态trigger为true触发时发射子弹
//基本为StarRite特化使用
void rotate_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    if(bullet.bulletconfig_->shareconfig_.active_)
    {
        switch(*(bullet.bulletconfig_->shareconfig_.phase_))
        {
        case 1:
            {
                if(bullet.bulletconfig_->x_>0)
                {
                    bullet.bulletconfig_->x_=bullet.bulletconfig_->x_-abs(bullet.bulletconfig_->v_);
                    if(bullet.bulletconfig_->x_<0)
                    {
                        bullet.bulletconfig_->x_=0;
                    }
                    sf::Vector2f direction=bullet.getPosition()-bullet.bulletconfig_->center_point_;
                    direction=roundwithCenter({0,0},direction,bullet.bulletconfig_->v_);
                    bullet.setPosition(bullet.bulletconfig_->center_point_+direction);
                }
                else
                {
                    bullet.bulletconfig_->v_=0;
                }
                break;
            }

        case 2:
            {
                bullet.bulletconfig_->v_=bullet.bulletconfig_->v_+bullet.bulletconfig_->a_;
                if((bullet.bulletconfig_->v_)>(bullet.bulletconfig_->v2_))
                {
                    bullet.bulletconfig_->v_=bullet.bulletconfig_->v2_;
                }
                sf::Vector2f direction=bullet.getPosition()-bullet.bulletconfig_->center_point2_;
                direction=roundwithCenter({0,0},direction,bullet.bulletconfig_->v_);
                bullet.setPosition(bullet.bulletconfig_->center_point2_+direction);
                break;
            }
        
        default:
            break;
        }
        if(*(bullet.bulletconfig_->shareconfig_.trigger_))
        {
            //std::cout<<"111"<<std::endl;
            bullet.sonconfig_->spawn_point_=bullet.getPosition();
            bullet.sonconfig_->bulletclass_=DirectBullet2;
            bullet.sonconfig_->v_=0;
            bullet.sonconfig_->r_=bullet.bulletconfig_->r2_;
            bullet.sonconfig_->v2_=bullet.bulletconfig_->v3_;
            bullet.sonconfig_->a_=bullet.bulletconfig_->a2_;
            bullet.sonconfig_->clock1_.set_target(bullet.bulletconfig_->clock1_.get_target());
            bullet.sonconfig_->bullet_index_=bullet.bulletconfig_->bullet_index2_;
            bullet.sonconfig_->bulletbehavior_=bullet.bulletconfig_->bulletbehavior2_;
            if(bullet.bulletconfig_->random_son_direction_)
            {
                bullet.sonconfig_->direction_=roundwithCenter({0,0},{0,1},getRandomNum(0,360));
            }
            else
            {
                bullet.sonconfig_->direction_=bullet.bulletconfig_->direction_;
            }
            //std::cout<<"222"<<std::endl;

            resource->bulletmanager_.add_process(bullet.sonconfig_.get(),bullet.getEffectConfig());
            ///std::cout<<"333"<<std::endl;
        }
    }
    else
    {
        bullet.markDead();
    }
}

void rotate_move3(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    if(bullet.bulletconfig_->shareconfig_.active_)
    {
        switch (*(bullet.bulletconfig_->shareconfig_.phase_))
        {
        case 1:
            {
                bullet.setPosition(bullet.getPosition());
                break;
            }

        case 2:
            {
                sf::Vector2f direction=normalize(bullet.getPosition()-bullet.bulletconfig_->center_point_);

                bullet.setPosition(roundwithCenter(bullet.bulletconfig_->center_point_,bullet.getPosition(),bullet.bulletconfig_->rotate_angle_));
                bullet.setPosition(bullet.getPosition()+(bullet.bulletconfig_->v_)*direction);
                
                bullet.bulletconfig_->v_=bullet.bulletconfig_->v_+bullet.bulletconfig_->a_;
                if(bullet.bulletconfig_->v_>bullet.bulletconfig_->v2_)
                {
                    bullet.bulletconfig_->v_=bullet.bulletconfig_->v2_;
                }
                break;
            }
        
        default:
            {
                bullet.setPosition(bullet.getPosition());
                break;
            }
        }
    }
    else
    {
        bullet.markDead();
    }
}

UpdateFunc update_table[]=
{
    aim_move1,
    direct_move1,
    direct_move1,
    direct_move2,
    aim_move2,
    direct_move3,
    gravity_move,
    rotate_move1,
    behavior_move1,
    rotate_move2,
    rotate_move3
};