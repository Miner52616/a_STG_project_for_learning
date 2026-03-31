#include "behaviors/behaviors/RandomShake.h"
#include "mathematics/mathematics.h"
#include "ui/Button.h"

RandomShake::RandomShake(Button* button,sf::Vector2f centerposition,float shake_range,int shake_time):
    button_(button),centerposition_(centerposition),shake_range_(shake_range),clock_(0)
{
    clock_.set_target(shake_time);
}

void RandomShake::update()
{
    if(!clock_.get_condition())
    {
        nextposition_=centerposition_+sf::Vector2f{getRandomNum(-shake_range_,shake_range_),getRandomNum(-shake_range_,shake_range_)};
        button_->setButtonPosition(nextposition_);
    }
    else
    {
        button_->setButtonPosition(centerposition_);
    }
    clock_.count();
}

void RandomShake::reset()
{
    clock_.reset();
}

void RandomShake::setPosition(sf::Vector2f position)
{
    centerposition_=position;
}