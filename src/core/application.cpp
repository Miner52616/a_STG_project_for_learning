#include "core/application.h"
//#include "core/StateStack.h"
#include "states/MenuState.h"
#include <iostream>

application::application():
    stack_(*(this)),
    window_(sf::VideoMode({1280,960}),"thwss_0.0.2.2"),
    mainFont_("assets/fonts/abc.ttf"),
    playerTexture_("assets/textures/player.png"),
    enemyTexture_("assets/textures/enemy.png"),
    bulletTexture_("assets/textures/bullet.png"),
    score_dropTexture_("assets/textures/score_drop.png"),
    power_dropTexture_("assets/textures/power_drop.png"),
    child_planeTexture_("assets/textures/child_plane.png"),
    lifeUI_("assets/textures/life.png"),
    bombUI_("assets/textures/bomb.png"),
    spellnumUI_("assets/textures/spell_num.png"),
    LeiTanTexture_("assets/textures/LeiTan.png"),
    LeiTan_AirTexture_("assets/textures/LeiTan_Air.png"),
    overlay1Texture_("assets/textures/overlay1.png"),
    blossom_small_bulletTexture("assets/textures/blossom_small.png"),
    red_light_bulletTexture_("assets/textures/red_light_bullet.png"),
    blue_light_bulletTexture_("assets/textures/blue_light_bullet.png"),
    deep_blue_light_bulletTexture_("assets/textures/deep_blue_light_bullet.png"),
    hitboxTexture_("assets/textures/hitbox.png"),
    Air_1_1Texture_("assets/textures/air/air1.png"),
    Air_1_2Texture_("assets/textures/air/air2.png"),
    Air_1_3Texture_("assets/textures/air/air3.png"),
    Air_1_4Texture_("assets/textures/air/air4.png"),
    Air_1_5Texture_("assets/textures/air/air5.png"),
    Air_1_6Texture_("assets/textures/air/air6.png"),
    Air_1_7Texture_("assets/textures/air/air7.png"),
    Air_1_8Texture_("assets/textures/air/air8.png"),
    bulletsheetTexture_("assets/textures/sheets/bullet_sheet.png"),
    bulletsheetTexture2_("assets/textures/sheets/big_bullet_sheet.png"),
    playersheetTexture_("assets/textures/sheets/player_sheet.png"),
    effectsheetTexture_("assets/textures/sheets/effect_sheet.png")
{
    window_.setVerticalSyncEnabled(false);
    window_.setFramerateLimit(60);
    gameview_.setSize({1280,960});
    gameview_.setCenter({640,480});
    applyLetterBox();
    window_.setView(gameview_);
    stack_.push(std::make_unique<MenuState>(*this));

    history_data_=lua_.loadSave();
    //std::cout <<history_data_.high_score_<<std::endl;
    //std::cout <<history_data_.cleared_<<std::endl;
}

bool application::IsRunning() const
{
    return window_.isOpen();
}

void application::ProcessEvent()
{
    //状态栈逐个处理事件
    while(const auto event=window_.pollEvent())
    {
        stack_.ProcessEvent(window_,event);
    }
}

void application::Update()
{
    stack_.Update();
}

void application::Render()
{
    window_.clear();
    stack_.Render(window_);
    window_.display();
}

void application::End_operation()
{
    stack_.applyStateChanges();
}

void application::applyLetterBox()
{
    float windowRatio =
        window_.getSize().x / static_cast<float>(window_.getSize().y);
    float viewRatio =
        gameview_.getSize().x / gameview_.getSize().y;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;

    if (windowRatio > viewRatio)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1.f - sizeX) / 2.f;
    }
    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1.f - sizeY) / 2.f;
    }

    gameview_.setViewport(sf::FloatRect({posX, posY},{sizeX, sizeY}));
}