#include "overlays/overlays/texturecurtains/MissCurtain.h"
#include "mathematics/mathematics.h"
#include <iostream>

MissCurtain::MissCurtain(sf::Texture& texture):
    TextureCurtain(texture),
    position_({0,0}),
    second_circle_(48),
    expand_velocity_(20),
    cache_sprite_(cache1_.getTexture()),
    cache1_({770,900}),
    cache2_({770,900})
{
    initialize();
}

MissCurtain::MissCurtain(sf::Texture& texture,sf::Shader& shader):
    TextureCurtain(texture,shader),
    position_({0,0}),
    second_circle_(24),
    expand_velocity_(20),
    cache_sprite_(cache1_.getTexture()),
    cache1_({770,900}),
    cache2_({770,900})
{
    initialize();
}

void MissCurtain::initialize()
{
    flip_=true;
    cache_sprite_.setScale({1,-1});
    cache_sprite_.setPosition({0,900});
    for(int i=1;i<=6;i++)
    {
        sf::CircleShape circle;
        circle.setOrigin(circle.getLocalBounds().getCenter());

        circle.setRadius(1001);
        circle.setTexture(texture_);
        circle.setScale({1,-1});
        circles_.emplace_back(circle);
    }
}

void MissCurtain::reset()
{
    for(auto it=circles_.begin();it!=circles_.end();++it)
    {
        it->setRadius(0);
    }
    second_circle_.reset();
}

void MissCurtain::setPosition(sf::Vector2f position)
{
    position_={(int)position.x,(int)position.y};

    circles_[0].setPosition(position_);
    circles_[1].setPosition(position_+sf::Vector2f{-80,0});
    circles_[2].setPosition(position_+sf::Vector2f{0,-80});
    circles_[3].setPosition(position_+sf::Vector2f{80,0});
    circles_[4].setPosition(position_+sf::Vector2f{0,80});
    circles_[5].setPosition(position_);
}

sf::Vector2f MissCurtain::getPosition()
{
    return position_;
}

void MissCurtain::update()
{
    for(int i=1;i<=5;i++)
    {
        if(circles_[i-1].getRadius()<=1000)
        {
            circles_[i-1].setRadius((int)(circles_[i-1].getRadius()+expand_velocity_));
        }
    }
    if(second_circle_.get_condition())
    {
        if(circles_[5].getRadius()<=1000)
        {
            circles_[5].setRadius((int)(circles_[5].getRadius()+expand_velocity_));
        }
    }
    for(auto it=circles_.begin();it!=circles_.end();++it)
    {
        float rx=it->getLocalBounds().size.x/2;
        float ry=it->getLocalBounds().size.y/2;
        it->setOrigin(it->getLocalBounds().getCenter());
        sf::Vector2f position=it->getPosition();
        it->setTextureRect({{round_off(position.x-rx),round_off(900-(position.y-ry)-2*ry)},{round_off(2*rx),round_off(2*ry)}});
    }

    second_circle_.count();
}

void MissCurtain::render(sf::RenderTexture& texture)
{
    /*
    cache1_.clear();

    sf::Sprite sprite(texture.getTexture());
    sprite.setPosition({150,150});

    cache1_.draw(sprite);

    sf::Sprite result(cache1_.getTexture());

    texture.draw(result);
    */
    /*
    cache_sprite_.setScale({1,-1});
    cache_sprite_.setPosition({0,900});

    cache_sprite_.setTexture(texture.getTexture(),true);
    cache1_.clear();
    cache1_.draw(cache_sprite_);

    circles_[0].setTexture(&cache1_.getTexture());
    cache_sprite_.setTexture(cache1_.getTexture(),true);
    cache2_.clear();
    cache2_.draw(cache_sprite_);
    cache2_.draw(circles_[0],states_);
    
    cache_sprite_.setTexture(cache2_.getTexture(),true);
    texture.draw(cache_sprite_);
    */

    /*
    circles_[0].setTexture(&texture.getTexture());
    texture.draw(circles_[0],states_);

    circles_[1].setTexture(&texture.getTexture());
    texture.draw(circles_[1],states_);
    */
    if(circles_[5].getRadius()<=1000)
    {
        cache_sprite_.setTexture(texture.getTexture(),true);
        cache1_.clear();
        cache1_.draw(cache_sprite_);

        for(int i=1;i<=6;i++)
        {
            if((i%2)==1)
            {
                circles_[i-1].setTexture(&cache1_.getTexture());
                cache_sprite_.setTexture(cache1_.getTexture());
                //cache_sprite_.setScale({1,-1});
                cache2_.clear();
                cache2_.draw(cache_sprite_);
                cache2_.draw(circles_[i-1],states_);
            }
            else
            {
                circles_[i-1].setTexture(&cache2_.getTexture());
                cache_sprite_.setTexture(cache2_.getTexture());
                //cache_sprite_.setScale({1,-1});
                cache1_.clear();
                cache1_.draw(cache_sprite_);
                cache1_.draw(circles_[i-1],states_);
            }
        }

        //std::cout<<texture.getSize().x<<std::endl;
        //std::cout<<cache1_.getSize().x<<std::endl;
        //std::cout<<cache2_.getSize().x<<std::endl;

        cache_sprite_.setTexture(cache1_.getTexture());
        texture.draw(cache_sprite_);
    }
}