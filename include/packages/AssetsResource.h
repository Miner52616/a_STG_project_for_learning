#pragma once
#include <SFML/Graphics.hpp>

class AssetsResource
{
public:
    //字体，图片，遮罩，存档配置资源
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

public:
    AssetsResource();
};