#pragma once
#include "core/state.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Bullet.h"

class GameState:public State
{
private:
    long long int frame_;
    Player player_;
    Enemy enemy1_;

    std::vector<std::unique_ptr<Bullet>> player_bulletlist;

public:
    void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;

public:
    GameState(application &app);

protected:
    void player_bulletlist_update();

protected:
    void player_bulletlist_move();
    void player_bulletlist_clear();
    void player_bulletlist_add();
    void player_bulletlist_drawwindow(sf::RenderWindow& window);
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Closed);
    void HandleEvent(sf::RenderWindow& window,auto){};
};