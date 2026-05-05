#include "phases/phases/SpellPhase.h"
#include "manager/BulletManager.h"
#include "manager/CollisionSystem.h"
#include "manager/EffectManager.h"
#include "mathematics/mathematics.h"
#include "bullets/LinearBullet.h"
#include "entities/Boss.h"

SpellPhase::SpellPhase(Resource* resource,YellowPage* yellowpage,int target_frame):
    TimePhase(resource,yellowpage,target_frame),boss_(NULL),moveclock_(240),shootclock_(60),nextposition_(460,200),fullHP_(1000),HP_(1000),voidspell_(false),spellname_(resource->app_.mainFont_),timer_(resource->app_.mainFont_),spellnum_(resource->app_.mainFont_,resource->app_.spellnumUI_),
    overlayconfig_(resource->app_.playerTexture_),spellcard_(false)
{
    setHP(600);
    spellnum_.setLinePosition({10,25});
    spellnum_.setLineSize(20);
    spellnum_.setInitialGap(0);
    spellnum_.setY_Gap(25);
    spellnum_.setGap(25);
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

    if(isDead())
    {
        //Spell结束，切换至下一个Spell前最后的操作在此完成
        if(!voidspell_)
        {
            if(spellcard_)
            {
                overlayconfig_.overlaytype_=OverlayType::Text_Overlay;
                overlayconfig_.color_alpha_=255;
                overlayconfig_.time_=180;
                overlayconfig_.change_origin_=true;
                
                if(!(yellowpage_->player_->isMissed()))
                {
                    overlayconfig_.text_="Get Spell Card Bonus!!";
                    overlayconfig_.text_size_=50;
                    overlayconfig_.spawn_position_={670,200};
                    resource_->effectmanager_.add_process(&overlayconfig_);
                    int bonus=30000+10*(target_frame_-frame_);
                    overlayconfig_.text_="+"+std::to_string(bonus);
                    overlayconfig_.spawn_position_={670,265};
                    resource_->effectmanager_.add_process(&overlayconfig_);
                    yellowpage_->score_line_.setCurrentNum(yellowpage_->score_line_.getCurrentNum()+bonus);
                }
                else
                {
                    overlayconfig_.text_="Spell Card Bonus";
                    overlayconfig_.text_size_=40;
                    overlayconfig_.spawn_position_={540,180};
                    resource_->effectmanager_.add_process(&overlayconfig_);
                    int bonus=(30000+10*(target_frame_-frame_))*0.65;
                    overlayconfig_.text_="+"+std::to_string(bonus);
                    overlayconfig_.spawn_position_={540,230};
                    resource_->effectmanager_.add_process(&overlayconfig_);
                    yellowpage_->score_line_.setCurrentNum(yellowpage_->score_line_.getCurrentNum()+bonus);
                }
            }
        }
        yellowpage_->player_->setMissed(false);
        resource_->bulletmanager_.clear_enemybullet();
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
    spellnum_.render(texture);
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

bool SpellPhase::isDead() const
{
    if((isTimeup())||(HP_<=0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SpellPhase::setSpellCard(bool spellcard)
{
    spellcard_=spellcard;
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
    spellname_.changeOrigin(true);
}

void SpellPhase::setTextPosition(sf::Vector2f position)
{
    spellname_.setPosition(position);
}

void SpellPhase::setBossName_SpellNum(const std::string text,int num)
{
    spellnum_.setLineText(text);
    spellnum_.setCurrentNum(num);
}