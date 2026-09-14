#pragma once
#include "core/LuaManager.h"
#include <SFML/Graphics.hpp>
#include "core/StateStack.h"
#include "packages/AssetsResource.h"

//应用，整个游戏就是一个应用的实例
class Application
{
public:
    //窗口与应用系统资源/系统本身
    //窗口资源需要作为参数传入使用，以明确窗口
    sf::View gameview_;
    sf::RenderWindow window_;
    LuaManager lua_;
    StateStack stack_;

public:
    //字体，图片，遮罩，存档配置资源
    //其它资源通过application指针或者引用使用
    AssetsResource assets_resource_;
    /*
    sf::Font mainFont_;
    sf::Texture playerTexture_;
    sf::Texture enemyTexture_;
    sf::Texture bulletTexture_;
    sf::Texture score_dropTexture_;
    sf::Texture power_dropTexture_;
    sf::Texture child_planeTexture_;
    sf::Texture lifeUI_;
    sf::Texture bombUI_;
    sf::Texture spellnumUI_;
    sf::Texture LeiTanTexture_;
    sf::Texture LeiTan_AirTexture_;
    sf::Texture overlay1Texture_;
    sf::Texture blossom_small_bulletTexture;
    sf::Texture red_light_bulletTexture_;
    sf::Texture blue_light_bulletTexture_;
    sf::Texture deep_blue_light_bulletTexture_;
    sf::Texture hitboxTexture_;

    sf::Texture Air_1_1Texture_;
    sf::Texture Air_1_2Texture_;
    sf::Texture Air_1_3Texture_;
    sf::Texture Air_1_4Texture_;
    sf::Texture Air_1_5Texture_;
    sf::Texture Air_1_6Texture_;
    sf::Texture Air_1_7Texture_;
    sf::Texture Air_1_8Texture_;

    sf::Texture bulletsheetTexture_;
    sf::Texture playersheetTexture_;
    sf::Texture bulletsheetTexture2_;
    sf::Texture effectsheetTexture_;

    sf::Texture curtain_texture1_;

    sf::Texture void_texture_;

    sf::Shader color_flip_;
    */

    SaveData history_data_;

private:
    bool isRunning() const;  //窗口是否还在打开着
    void processEvent();  //处理产生的所有事件
    void update();  //统一更新属性
    void render();  //统一渲染至屏幕
    void end_operation();  //一套流程中最后的操作
public:
    Application();  //初始化窗口属性，初始化资源加载，初始化状态栈
    void run();//app运行主循环
    void applyLetterBox();
};