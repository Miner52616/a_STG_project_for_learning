#include "phases/phases/SpellPhase.h"
#include "manager/BulletManager.h"
#include "manager/CollisionSystem.h"
#include "mathematics/mathematics.h"
#include "bullets/LinearBullet.h"
#include "entities/Boss.h"

SpellPhase::SpellPhase(Resource* resource,YellowPage* yellowpage,int target_frame):
    TimePhase(resource,yellowpage,target_frame),boss_(NULL),moveclock_(240),shootclock_(60),nextposition_(460,200),fullHP_(1000),HP_(1000),voidspell_(false),spellname_(resource->app_.mainFont_),timer_(resource->app_.mainFont_)
{
    setHP(600);
    HPline_.setFillColor(sf::Color::White);
    HPline_.setPosition({5,5});
    HPline_.setSize({760,8});
    timer_.setMaxNum(99);
    timer_.setLineText("");
    timer_.setLinePosition({335,35});
}

void SpellPhase::update()
{
    if(!voidspell_)
    HPline_.setSize({(760*HP_)/fullHP_,8});

    for(auto it=behaviorlist_.begin();it!=behaviorlist_.end();++it)
    {
        (*it)->update();
    }

    timer_.setCurrentNum((target_frame_-frame_)/60);
    /*
    boss_->store_position();
    boss_->setPosition((nextposition_-boss_->getPosition())*0.01f+boss_->getPosition());
    if(moveclock_.get_condition())
    {
        nextposition_={getRandomNum(125,795),getRandomNum(20,300)};
        moveclock_.reset();
    }

    if(shootclock_.get_condition())
    {
        bulletmanager_.add_process(std::make_unique<LinearBullet>(app_,app_.bulletTexture_,boss_->getPosition(),player_->getPosition(),0.06,6));
        shootclock_.reset();
    }
*/
    moveclock_.count();
    shootclock_.count();
    frame_++;

    if(isTimeup()||HP_<=0)
    {
        change_=true;
    }
}

void SpellPhase::render(sf::RenderWindow& window)
{
    boss_->drawwindow(window);
    if(!voidspell_)
    {
        window.draw(HPline_);
        timer_.render(window);
    }
    spellname_.render(window);
}

void SpellPhase::render(sf::RenderTexture& texture)
{
    boss_->drawtexture(texture);
    if(!voidspell_)
    {
        texture.draw(HPline_);
        timer_.render(texture);
    }
    spellname_.render(texture);
}

void SpellPhase::addBehavior(std::unique_ptr<Behavior> behavior)
{
    behaviorlist_.emplace_back(std::move(behavior));
}

void SpellPhase::setHP(float HP)
{
    fullHP_=HP;
    HP_=HP;
}

void SpellPhase::be_damage(float damage)
{
    if(!voidspell_)
    HP_=HP_-damage;
}

void SpellPhase::ProcessCollision()
{
    resource_->collisionsystem_.ProcessCollision(boss_);
}

void SpellPhase::setBoss(Boss* boss)
{
    boss_=boss;
}

sf::Vector2f SpellPhase::get_targetposition_for_LeiTan(AimMove2* move)
{
    return boss_->getPosition();
}

sf::Vector2f SpellPhase::get_closest_target(sf::Vector2f position)
{
    return boss_->getPosition();
}

void SpellPhase::setVoidSpell(bool isvoid)
{
    voidspell_=isvoid;
}

void SpellPhase::setTextName(const std::string text)
{
    spellname_.setTextText(text);
}

void SpellPhase::setTextPosition(sf::Vector2f position)
{
    spellname_.setPosition(position);
}