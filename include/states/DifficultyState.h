#pragma  once
#include "basicstates/ButtonState.h"
#include "overlays/overlays/Curtain1.h"

constexpr int DifButtonNum=4;

class DifficultyState:public ButtonState<DifficultyState>
{
private:
    int current_phase_;
    Curtain1 curtain_;

public:
    using ButtonState<DifficultyState>::HandleEvent;
    DifficultyState(Application &app);  //初始化所有按钮的属性
    void processEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);  //处理“按键按下”事件
};