#include "effects/Effect.h"
#include "packages/EffectConfig.h"
#include "core/application.h"
#include "mathematics/mathematics.h"

Effect::Effect(sf::Texture &texture):
    texture_(&texture),picture_(texture),position_({0,0}),prev_position_({0,0}),dead_(false),clock_(48),effectconfig_(texture),texture_clock_(4)
{
    texture_clock_.set_ready();
    clock_.reset();
}

Effect::Effect(sf::Texture &texture,sf::Vector2f position,long long int time):
    texture_(&texture),picture_(texture),position_(position),prev_position_({0,0}),dead_(false),clock_(time),effectconfig_(texture),texture_clock_(4)
{
    texture_clock_.set_ready();
    clock_.reset();
}

void Effect::setPosition(sf::Vector2f position)
{
    position_=position;
    picture_.setPosition(position_);
}

void Effect::store_position()
{
    prev_position_=position_;
}

sf::Vector2f Effect::getPosition()
{
    return position_;
}

sf::Vector2f Effect::getprevPosition()
{
    return prev_position_;
}

void Effect::setResource(Resource* resource)
{
    resource_=resource;
}

bool Effect::isDead() const
{
    return dead_;
}


void Effect::markDead()
{
    dead_=true;
}

void Effect::addBehavior(std::unique_ptr<Behavior> behavior)
{
    behaviorlist_.emplace_back(std::move(behavior));
}

void Effect::update()
{
    store_position();
    /*
    for(auto it=behaviorlist_.begin();it!=behaviorlist_.end();++it)
    {
        (*it)->update();
    }*/
    effect_update_table[effectconfig_.effecttype_](*this);

    clock_.count();
    if(clock_.get_condition())
    {
        markDead();
    }
}

void Effect::setDead(bool dead)
{
    dead_=dead;
}

void Effect::initialize()
{
    dead_=false;
}

void Effect::setActive(bool active)
{
    active_=active;
}

void Effect::rebuild(sf::Texture &texture,sf::Vector2f position)
{
    texture_=&texture;
    picture_.setTexture(*texture_,true);
    picture_.setOrigin(picture_.getLocalBounds().getCenter());
    prev_position_={0,0};
    dead_=false;
    clock_.set_target(48);

    setPosition(position);
    clock_.reset();
    texture_clock_.set_ready();

    rebuild_initialize();
}

void Effect::rebuild_initialize()
{
    if(effectconfig_.random_rotate_)
    {
        picture_.setRotation(sf::degrees(getRandomNum(0,360)));
    }
}

EffectConfig* Effect::getEffectConfig()
{
    return &effectconfig_;
}

void Effect::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
}

void Effect::drawtexture(sf::RenderTexture& texture)
{
    texture.draw(picture_);
}

void Effect::setTime(long long int time)
{
    clock_.set_target(time);
}

/******************************************************* */

//匀速直线运动
void direct_move1(Effect& effect)
{
    effect.setPosition(effect.getPosition()+effect.effectconfig_.v_*effect.effectconfig_.direction_);
}

//含加速度的减速至目标速度的减速运动
void direct_move2(Effect& effect)
{
    effect.setPosition(effect.getPosition()+effect.effectconfig_.v_*effect.effectconfig_.direction_);
    if(effect.effectconfig_.v_>effect.effectconfig_.v2_)
    {
        effect.effectconfig_.v_=effect.effectconfig_.v_-effect.effectconfig_.a_;
        if(effect.effectconfig_.v_<effect.effectconfig_.v2_)
        {
            effect.effectconfig_.v_=effect.effectconfig_.v2_;
        }
    }
}

void keep_static(Effect& effect)
{
    if(effect.texture_clock_.get_condition())
    {
        //std::cout<<"111"<<std::endl;
        effect.texture_clock_.reset();
        //std::cout<<effect.effectconfig_.current_texture_num_<<" "<<effect.effectconfig_.texturelist_size_-1<<std::endl;
        if(effect.effectconfig_.current_texture_num_<=effect.effectconfig_.texturelist_size_-1)
        {
            //std::cout<<"222"<<std::endl;
            effect.picture_.setTexture(*(effect.effectconfig_.texturelist_[effect.effectconfig_.current_texture_num_]),true);
            effect.picture_.setOrigin(effect.picture_.getLocalBounds().getCenter());

            effect.effectconfig_.current_texture_num_++;
        }
    }
    effect.texture_clock_.count();
}

void keep_static2(Effect& effect)
{
    if(effect.texture_clock_.get_condition())
    {
        //std::cout<<"111"<<std::endl;
        effect.texture_clock_.reset();
        //std::cout<<effect.effectconfig_.current_texture_num_<<" "<<effect.effectconfig_.texturelist_size_-1<<std::endl;
        if(effect.effectconfig_.current_texture_num_<=effect.effectconfig_.texturelist_size_-1)
        {
            //std::cout<<"222"<<std::endl;
            std::vector<int> rect=playersheet_effect_transform(effect.effectconfig_.effect_index_);
            sf::Vector2i position={rect[0],rect[1]};
            sf::Vector2i size={rect[2],rect[3]};
            effect.picture_.setTextureRect({position,size});
            effect.picture_.setOrigin(effect.picture_.getLocalBounds().getCenter());

            effect.effectconfig_.effect_index_[0]++;
            effect.effectconfig_.current_texture_num_++;
        }
    }
    effect.texture_clock_.count();
}

EffectUpdateFunc effect_update_table[]=
{
    direct_move2,
    keep_static,
    keep_static2
};