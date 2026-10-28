#pragma once
#include "basicstates/ButtonState.h"
#include "ui/KeyBoard.h"

constexpr int ReplayButtonNum=30;

class GameState;

class ReplayState:public ButtonState<ReplayState>
{
private:
    GameState* game_=nullptr;
    KeyBoard keyboard_;
    sf::Vector2f target_position_;
    sf::Vector2f current_position_;

    bool save_mode_=false;

    std::vector<sf::Vector2f> button_target_position_;
    int phase_=1;

private:
    void load_replay();
public:
    using ButtonState<ReplayState>::HandleEvent;

    ReplayState(Application &app,GameState* game=nullptr);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);

};