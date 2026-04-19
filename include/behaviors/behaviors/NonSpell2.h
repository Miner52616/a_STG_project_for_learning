#pragma once
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

class NonSpell2_1:public Behavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;

    int bullet_num_;
    sf::Vector2f start_position_;
    sf::Vector2f set_direction_;
    sf::Vector2f bullet_direction_;
    float gap_;

    Clock start_clock_;
    Clock shoot_clock_;
private:
    void setBulletConfig();
    //void rotate();
public:
    NonSpell2_1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell2_2:public Behavior
{
protected:
    Entity* entity_;
    BulletConfig bulletconfig_;

    int bullet_num_;
    int group_num_;
    float gap_;
    
    int delaytime_;
    bool get_center;
    float rotate_degree_;
    sf::Vector2f center_;
    sf::Vector2f start_position_;
    sf::Vector2f set_direction_;
    sf::Vector2f bullet_direction_;
    sf::Vector2f bullet_direction2_;
    std::vector<sf::Vector2f> direction_list;

    Clock shoot_clock_;
    Clock shoot_num_;
    Clock shoot_num2_;

protected:
    void setBulletConfig();
    void reset();
public:
    NonSpell2_2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell2_2_1:public NonSpell2_2
{
public:
    NonSpell2_2_1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell2_2_2:public NonSpell2_2
{
private:
    Clock start_clock_;

public:
    NonSpell2_2_2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell2_3:public Behavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;

    int bullet_num_;
    sf::Vector2f start_position_;
    sf::Vector2f set_direction_;
    sf::Vector2f bullet_direction_;
    float gap_;

    Clock start_clock_;
    Clock shoot_clock_;
private:
    void setBulletConfig();
    //void rotate();
public:
    NonSpell2_3(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell2:public Behavior
{
private:
    NonSpell2_1 nonspell2_1;
    NonSpell2_2_1 nonspell2_2_1;
    NonSpell2_2_2 nonspell2_2_2;
    NonSpell2_3 nonspell2_3;

public:
    NonSpell2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};