#pragma once
#include "overlays/overlays/TextureCurtain.h"
#include "entities/Entity.h"
#include "core/Clock.h"
#include <vector>

std::vector<sf::Vertex> getStarTriangleVertex(sf::Vector2f position,float angle,float r);

class StarConfig
{
public:
    sf::Vector2f target_position_={0,0};
    float target_angle_=0;
    float target_r_=100;
    Clock clock_;

public:
    StarConfig();
};

class Star
{
private:
    float r_=100;
    sf::Vector2f position_={0,0};
    float angle_=0;

    StarConfig config_;
public:
    StarConfig* getConfig();
    void setPosition(sf::Vector2f position);
    void setAngle(float angle);
    void setR(float r);
    float getAngle();
    sf::Vector2f getPosition();
    float getR();
    void update();
};

class StarCurtain:public TextureCurtain
{
private:
    int num_x_;
    int num_y_;
    sf::Vector2f start_position_;
    sf::Vector2f target_position_;
    float target_angle_;
    int mode_=1;

    std::vector<std::vector<Star>> star_matrix_;

public:
    StarCurtain(sf::Texture& texture);
    void setNum(int num_x,int num_y);
    void setStart_Target(sf::Vector2f start_position,sf::Vector2f target_position,float target_angle);

    void update() override;
};

class StarCurtain2:public TextureCurtain
{
private:
    std::vector<Star> star_list_;

public:
    StarCurtain2(sf::Texture& texture);
    void add_star(Star& star);
    
    void update() override;
};