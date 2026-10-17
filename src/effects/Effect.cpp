#include "effects/Effect.h"
#include "packages/EffectConfig.h"
#include "core/Application.h"
#include "mathematics/mathematics.h"

Effect::Effect(sf::Texture &texture,sf::Font& font):
    texture_(&texture),picture_(texture),font_(&font),text_(font),position_({0,0}),prev_position_({0,0}),dead_(false),clock_(48),effectconfig_(texture),texture_clock_(4)
{
    texture_clock_.set_ready();
    clock_.reset();
}

Effect::Effect(sf::Texture &texture,sf::Font& font,sf::Vector2f position,long long int time):
    texture_(&texture),picture_(texture),font_(&font),text_(font),position_(position),prev_position_({0,0}),dead_(false),clock_(time),effectconfig_(texture),texture_clock_(4)
{
    texture_clock_.set_ready();
    clock_.reset();
}

void Effect::setPosition(sf::Vector2f position)
{
    position_=position;
    picture_.setPosition(position_);
    text_.setTextPosition(position_);
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

/*
void Effect::setResource(Resource* resource)
{
    resource_=resource;
}
    */

bool Effect::isDead() const
{
    return dead_;
}


void Effect::markDead()
{
    dead_=true;
}

/*
void Effect::addBehavior(std::unique_ptr<Behavior> behavior)
{
    behaviorlist_.emplace_back(std::move(behavior));
}
    */

void Effect::update()
{
    store_position();
    
    effect_update_table[static_cast<std::size_t>(effectconfig_.effecttype_)](*this);

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

void Effect::rebuild()
{
    texture_=effectconfig_.texture_;
    picture_.setTexture(*texture_,true);

    //font_=effectconfig_.font_;

    switch (effectconfig_.effecttype_)
    {
    case EffectType::LeiTan_Air:
        break;
    
    case EffectType::Bullet_Air:
        {
            Two_Vector2i rect=effectsheet_transform(effectconfig_.effect_index_);
            sf::Vector2i position={rect.vec1_.x, rect.vec1_.y};
            sf::Vector2i size={rect.vec2_.x, rect.vec2_.y};
            picture_.setTextureRect({position,size});
            break;
        }

    case EffectType::PlayerBullet_Air:
        {
            Two_Vector2i rect=playersheet_effect_transform(effectconfig_.effect_index_);
            sf::Vector2i position={rect.vec1_.x, rect.vec1_.y};
            sf::Vector2i size={rect.vec2_.x, rect.vec2_.y};
            picture_.setTextureRect({position,size});
            break;
        }
    
    default:
        break;
    }

    picture_.setScale({1.414,1.414});
    picture_.setOrigin(picture_.getLocalBounds().getCenter());
    if(effectconfig_.random_rotate_)
    {
        //std::cout<<"rotate"<<std::endl;
        picture_.setRotation(sf::degrees(getRandomNum(0,360)));
    }
    else
    {
        //std::cout<<"no rotate"<<std::endl;
        picture_.setRotation(sf::degrees(90));
    }

    picture_.setColor(sf::Color{255,255,255,effectconfig_.color_alpha_});

    text_.setTextText(effectconfig_.text_);
    text_.setTextSize(effectconfig_.text_size_);
    text_.setOriginCenter();

    prev_position_={0,0};
    dead_=false;

    setPosition(effectconfig_.spawn_point_);

    setTime(effectconfig_.time_);
    clock_.reset();
    texture_clock_.set_ready();

    //rebuild_initialize();
}

/*
void Effect::rebuild(sf::Texture &texture,sf::Vector2f position)
{
    texture_=&texture;
    picture_.setTexture(*texture_,true);
    switch (effectconfig_.effecttype_)
    {
    case LeiTan_Air:
        break;
    
    case Bullet_Air:
        {
            Two_Vector2i rect=effectsheet_transform(effectconfig_.effect_index_);
            sf::Vector2i position={rect.vec1_.x, rect.vec1_.y};
            sf::Vector2i size={rect.vec2_.x, rect.vec2_.y};
            picture_.setTextureRect({position,size});
            break;
        }

    case PlayerBullet_Air:
        {
            Two_Vector2i rect=playersheet_effect_transform(effectconfig_.effect_index_);
            sf::Vector2i position={rect.vec1_.x, rect.vec1_.y};
            sf::Vector2i size={rect.vec2_.x, rect.vec2_.y};
            picture_.setTextureRect({position,size});
            break;
        }
    
    default:
        break;
    }
    picture_.setScale({1.414,1.414});
    picture_.setOrigin(picture_.getLocalBounds().getCenter());
    prev_position_={0,0};
    dead_=false;
    clock_.set_target(48);

    setPosition(position);
    clock_.reset();
    texture_clock_.set_ready();

    rebuild_initialize();
}
    */

/*
void Effect::rebuild_initialize()
{
    if(effectconfig_.random_rotate_)
    {
        //std::cout<<"rotate"<<std::endl;
        picture_.setRotation(sf::degrees(getRandomNum(0,360)));
    }
    else
    {
        //std::cout<<"no rotate"<<std::endl;
        picture_.setRotation(sf::degrees(90));
    }

    picture_.setColor(sf::Color{255,255,255,effectconfig_.color_alpha_});
}
    */

EffectConfig* Effect::getEffectConfig()
{
    return &effectconfig_;
}

void Effect::drawwindow(sf::RenderWindow& window)
{
    if(effectconfig_.isText)
    {
        text_.DrawText(window);
    }
    else
    {
        window.draw(picture_);
    }
}

void Effect::drawtexture(sf::RenderTexture& texture)
{
    if(effectconfig_.isText)
    {
        text_.DrawText(texture);
    }
    else
    {
        texture.draw(picture_);
    }
}

void Effect::setTime(long long int time)
{
    clock_.set_target(time);
}

/******************************************************* */

//匀速直线运动
/*
void EffectUpdateTableLibrary::direct_move1(Effect& effect)
{
    effect.setPosition(effect.getPosition()+effect.effectconfig_.v_*effect.effectconfig_.direction_);
}
    */

//含加速度的减速至目标速度的减速运动
void EffectUpdateTableLibrary::direct_move2(Effect& effect)
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

void EffectUpdateTableLibrary::keep_static(Effect& effect)
{
    if(effect.texture_clock_.get_condition())
    {
        //std::cout<<"111"<<std::endl;
        effect.texture_clock_.reset();
        //std::cout<<effect.effectconfig_.current_texture_num_<<" "<<effect.effectconfig_.texturelist_size_-1<<std::endl;
        if(effect.effectconfig_.current_texture_num_<=effect.effectconfig_.texturelist_size_-1)
        {
            //std::cout<<"222"<<std::endl;
            Two_Vector2i rect=effectsheet_transform(effect.effectconfig_.effect_index_);
            sf::Vector2i position={rect.vec1_.x, rect.vec1_.y};
            sf::Vector2i size={rect.vec2_.x, rect.vec2_.y};
            effect.picture_.setTextureRect({position,size});
            effect.picture_.setOrigin(effect.picture_.getLocalBounds().getCenter());

            effect.effectconfig_.effect_index_.x++;
            effect.effectconfig_.current_texture_num_++;
            
            //effect.picture_.setTexture(*(effect.effectconfig_.texturelist_[effect.effectconfig_.current_texture_num_]),true);
            //effect.picture_.setOrigin(effect.picture_.getLocalBounds().getCenter());

            //effect.effectconfig_.current_texture_num_++;
        }
    }
    effect.texture_clock_.count();
}

void EffectUpdateTableLibrary::keep_static2(Effect& effect)
{
    effect.setPosition(effect.getPosition()+effect.effectconfig_.v_*effect.effectconfig_.direction_);
    if(effect.texture_clock_.get_condition())
    {
        //std::cout<<"111"<<std::endl;
        effect.texture_clock_.reset();
        //std::cout<<effect.effectconfig_.current_texture_num_<<" "<<effect.effectconfig_.texturelist_size_-1<<std::endl;
        if(effect.effectconfig_.current_texture_num_<=effect.effectconfig_.texturelist_size_-1)
        {
            //std::cout<<"222"<<std::endl;
            Two_Vector2i rect=playersheet_effect_transform(effect.effectconfig_.effect_index_);
            sf::Vector2i position={rect.vec1_.x, rect.vec1_.y};
            sf::Vector2i size={rect.vec2_.x, rect.vec2_.y};
            effect.picture_.setTextureRect({position,size});
            effect.picture_.setOrigin(effect.picture_.getLocalBounds().getCenter());

            effect.effectconfig_.effect_index_.x++;
            effect.effectconfig_.current_texture_num_++;
        }
    }
    effect.texture_clock_.count();
}

void EffectUpdateTableLibrary::void_update(Effect& effect)
{
    ;
}

EffectUpdateFunc effect_update_table[]=
{
    EffectUpdateTableLibrary::direct_move2,
    EffectUpdateTableLibrary::keep_static,
    EffectUpdateTableLibrary::keep_static2,
    EffectUpdateTableLibrary::void_update
};