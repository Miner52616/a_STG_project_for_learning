#include "mathematics/mathematics.h"
#include "entities/Enemy.h"
#include <random>
#include <math.h>
#include <iostream>

float distancePointToSegment(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b)
{
    sf::Vector2f ab=b-a;
    sf::Vector2f ap=p-a;

    float t=ap.dot(ab)/ab.dot(ab);
    t=std::clamp(t,0.f,1.f);

    sf::Vector2f closest=a+(ab*t);
    return (p-closest).length();
}

float distancePointToSegment2(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b)
{
    sf::Vector2f ab=b-a;
    sf::Vector2f ap=p-a;

    float t=ap.dot(ab)/ab.dot(ab);
    t=std::clamp(t,0.f,1.f);

    sf::Vector2f closest=a+(ab*t);

    sf::Vector2f vec=p-closest;

    return (vec.x)*(vec.x)+(vec.y)*(vec.y);
}

float getRandomNum(float a,float b)
{
    if(a>b)
    {
        std::swap(a,b);
    }
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis_double(a,b);

    return (float)dis_double(gen);
}

int the_min(int a,int b)
{
    if(a>=b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

int round_off(float num)
{
    float res=num-(int)num;
    if(res>=0.5)
    {
        return ((int)num+1);
    }
    else
    {
        return (int)num;
    }
}

sf::Vector2f roundwithCenter(sf::Vector2f center,sf::Vector2f point,float angle)
{
    float rad=angle*3.1415926/180;
    float cos_value=std::cos(rad);
    float sin_value=std::sin(rad);

    sf::Vector2f translated_point=point-center;

    float rotated_x=translated_point.x*cos_value-translated_point.y*sin_value;
    float rotated_y=translated_point.x*sin_value+translated_point.y*cos_value;

    sf::Vector2f rotated_point(rotated_x,rotated_y);

    return rotated_point+center;
}

sf::Vector2f round(sf::Vector2f Vector,float angle)
{
    float rad=angle*3.1415926/180;
    float cos_value=std::cos(rad);
    float sin_value=std::sin(rad);

    float rotated_x=Vector.x*cos_value-Vector.y*sin_value;
    float rotated_y=Vector.x*sin_value+Vector.y*cos_value;

    sf::Vector2f rotated_vector(rotated_x,rotated_y);

    return rotated_vector;
}

sf::Vector2f normalize(sf::Vector2f Vector)
{
    //这里用到了.length()，有开方。谨慎使用
    float length=Vector.length();
    if(length!=0)
    {
        return Vector/length;
    }
    else
    {
        return sf::Vector2f(0,0);
    }
}

sf::Vector2f get_randomposition_for_LeiTan(sf::Vector2f v)
{
    float width=getRandomNum(0,200);
    float length=getRandomNum(0,534);

    if(v.x>=0&&v.y>=0)
    {
        if(length<=385)
        {
            return {385+length,900-width};
        }
        else
        {
            return {770-width,900-200-(length-385)};
        }
    }
    else if(v.x<0&&v.y>=0)
    {
        if(length<=385)
        {
            return {385-length,900-width};
        }
        else
        {
            return {width,900-200-(length-385)};
        }
    }
    else if(v.x<0&&v.y<0)
    {
        if(length<=385)
        {
            return {385-length,width};
        }
        else
        {
            return {width,200+(length-385)};
        }
    }
    else
    {
        if(length<=385)
        {
            return {385+length,width};
        }
        else
        {
            return {770-width,200+(length-385)};
        }
    }

    return {0,0};
}

/*
long long int get_random_from(std::vector<long long int> vector)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis_int(0,vector.size()-1);

    return vector[dis_int(gen)];
}

Enemy* get_random_from(std::vector<Enemy*> vector)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis_int(0,vector.size()-1);

    return vector[dis_int(gen)];
}

int get_random_from(std::vector<int> vector)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis_int(0,vector.size()-1);
    return vector[dis_int(gen)];
}
*/

float RadTransToDegree(float rad)
{
    float degree=rad*180/std::numbers::pi;
    return degree;
}

//constexpr int BULLET_SHEET_GAP=16;

Two_Vector2i bulletsheet_transform(const sf::Vector2i& want)
{
    Two_Vector2i rect;

    //左上角点
    int x1=(want.x-1)*BULLET_SHEET_GAP;
    int y1=(want.y-1)*BULLET_SHEET_GAP;
    //边长
    int x_side=BULLET_SHEET_GAP;
    int y_side=BULLET_SHEET_GAP;

    rect.vec1_.x=x1;
    rect.vec1_.y=y1;
    rect.vec2_.x=x_side;
    rect.vec2_.y=y_side;

    return rect;
}

Two_Vector2i big_bulletsheet_transform(const sf::Vector2i& want)
{
    Two_Vector2i rect;

    //左上角点
    int x1=(want.x-1)*2*BULLET_SHEET_GAP;
    int y1=(want.y-1)*2*BULLET_SHEET_GAP;
    //边长
    int x_side=2*BULLET_SHEET_GAP;
    int y_side=2*BULLET_SHEET_GAP;

    rect.vec1_.x=x1;
    rect.vec1_.y=y1;
    rect.vec2_.x=x_side;
    rect.vec2_.y=y_side;

    return rect;
}

Two_Vector2i large_bulletsheet_transform(const sf::Vector2i& want)
{
    Two_Vector2i rect;

    //左上角点
    int x1=(want.x-1)*4*BULLET_SHEET_GAP;
    int y1=6*2*BULLET_SHEET_GAP;
    //边长
    int x_side=4*BULLET_SHEET_GAP;
    int y_side=4*BULLET_SHEET_GAP;

    rect.vec1_.x=x1;
    rect.vec1_.y=y1;
    rect.vec2_.x=x_side;
    rect.vec2_.y=y_side;

    return rect;
}

Two_Vector2i playersheet_bullet_transform(const sf::Vector2i& want)
{
    Two_Vector2i rect;

    //左上角点
    int x1=(want.x-1)*BULLET_SHEET_GAP;
    int y1=(want.y-1+11)*BULLET_SHEET_GAP;
    //边长
    int x_side=4*BULLET_SHEET_GAP;
    int y_side=BULLET_SHEET_GAP;

    rect.vec1_.x=x1;
    rect.vec1_.y=y1;
    rect.vec2_.x=x_side;
    rect.vec2_.y=y_side;

    return rect;
}

Two_Vector2i playersheet_effect_transform(const sf::Vector2i& want)
{
    Two_Vector2i rect;

    //左上角点
    int x1=(want.x-1)*BULLET_SHEET_GAP;
    int y1=(want.y-1+9)*BULLET_SHEET_GAP;
    //边长
    int x_side=BULLET_SHEET_GAP;
    int y_side=BULLET_SHEET_GAP;

    rect.vec1_.x=x1;
    rect.vec1_.y=y1;
    rect.vec2_.x=x_side;
    rect.vec2_.y=y_side;

    return rect;
}

Two_Vector2i effectsheet_transform(const sf::Vector2i& want)
{
    Two_Vector2i rect;

    //左上角点
    int x1;
    int y1;
    if(want.x<=4)
    {
        x1=(want.x-1)*4*BULLET_SHEET_GAP;
        y1=(want.y-1)*4*BULLET_SHEET_GAP;
    }
    else
    {
        x1=(want.x-5)*4*BULLET_SHEET_GAP;
        y1=(want.y)*4*BULLET_SHEET_GAP;
    }
    //边长
    int x_side=4*BULLET_SHEET_GAP;
    int y_side=4*BULLET_SHEET_GAP;

    rect.vec1_.x=x1;
    rect.vec1_.y=y1;
    rect.vec2_.x=x_side;
    rect.vec2_.y=y_side;

    return rect;
}