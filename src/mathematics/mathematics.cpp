#include "mathematics/mathematics.h"
#include "entities/Enemy.h"
#include <random>
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

std::vector<int> bulletsheet_transform(const std::vector<int>& want)
{
    std::vector<int> rect;
    rect.resize(4);

    if(want.size()!=2)
    {
        std::cout<<"sheet target dim wrong"<<std::endl;
        rect[0]=0;
        rect[1]=0;
        rect[2]=BULLET_SHEET_GAP;
        rect[3]=BULLET_SHEET_GAP;
    }
    else
    {
        //左上角点
        int x1=(want[0]-1)*BULLET_SHEET_GAP;
        int y1=(want[1]-1)*BULLET_SHEET_GAP;
        //边长
        int x_side=BULLET_SHEET_GAP;
        int y_side=BULLET_SHEET_GAP;

        rect[0]=x1;
        rect[1]=y1;
        rect[2]=x_side;
        rect[3]=y_side;
    }

    return rect;
}

std::vector<int> big_bulletsheet_transform(const std::vector<int>& want)
{
    std::vector<int> rect;
    rect.resize(4);

    if(want.size()!=2)
    {
        std::cout<<"sheet target dim wrong"<<std::endl;
        rect[0]=0;
        rect[1]=0;
        rect[2]=BULLET_SHEET_GAP;
        rect[3]=BULLET_SHEET_GAP;
    }
    else
    {
        //左上角点
        int x1=(want[0]-1)*2*BULLET_SHEET_GAP;
        int y1=(want[1]-1)*2*BULLET_SHEET_GAP;
        //边长
        int x_side=2*BULLET_SHEET_GAP;
        int y_side=2*BULLET_SHEET_GAP;

        rect[0]=x1;
        rect[1]=y1;
        rect[2]=x_side;
        rect[3]=y_side;
    }

    return rect;
}

std::vector<int> large_bulletsheet_transform(const std::vector<int>& want)
{
    std::vector<int> rect;
    rect.resize(4);

    if(want.size()!=2)
    {
        std::cout<<"sheet target dim wrong"<<std::endl;
        rect[0]=0;
        rect[1]=0;
        rect[2]=BULLET_SHEET_GAP;
        rect[3]=BULLET_SHEET_GAP;
    }
    else
    {
        //左上角点
        int x1=(want[0]-1)*4*BULLET_SHEET_GAP;
        int y1=6*2*BULLET_SHEET_GAP;
        //边长
        int x_side=4*BULLET_SHEET_GAP;
        int y_side=4*BULLET_SHEET_GAP;

        rect[0]=x1;
        rect[1]=y1;
        rect[2]=x_side;
        rect[3]=y_side;
    }

    return rect;
}

std::vector<int> playersheet_bullet_transform(const std::vector<int>& want)
{
    std::vector<int> rect;
    rect.resize(4);

    if(want.size()!=2)
    {
        std::cout<<"sheet target dim wrong"<<std::endl;
        rect[0]=0;
        rect[1]=0;
        rect[2]=BULLET_SHEET_GAP;
        rect[3]=BULLET_SHEET_GAP;
    }
    else
    {
        //左上角点
        int x1=(want[0]-1)*BULLET_SHEET_GAP;
        int y1=(want[1]-1+11)*BULLET_SHEET_GAP;
        //边长
        int x_side=4*BULLET_SHEET_GAP;
        int y_side=BULLET_SHEET_GAP;

        rect[0]=x1;
        rect[1]=y1;
        rect[2]=x_side;
        rect[3]=y_side;
    }

    return rect;
}

std::vector<int> playersheet_effect_transform(const std::vector<int>& want)
{
    std::vector<int> rect;
    rect.resize(4);

    if(want.size()!=2)
    {
        std::cout<<"sheet target dim wrong"<<std::endl;
        rect[0]=0;
        rect[1]=0;
        rect[2]=BULLET_SHEET_GAP;
        rect[3]=BULLET_SHEET_GAP;
    }
    else
    {
        //左上角点
        int x1=(want[0]-1)*BULLET_SHEET_GAP;
        int y1=(want[1]-1+9)*BULLET_SHEET_GAP;
        //边长
        int x_side=BULLET_SHEET_GAP;
        int y_side=BULLET_SHEET_GAP;

        rect[0]=x1;
        rect[1]=y1;
        rect[2]=x_side;
        rect[3]=y_side;
    }

    return rect;
}

std::vector<int> effectsheet_transform(const std::vector<int>& want)
{
    std::vector<int> rect;
    rect.resize(4);

    if(want.size()!=2)
    {
        std::cout<<"sheet target dim wrong"<<std::endl;
        rect[0]=0;
        rect[1]=0;
        rect[2]=4*BULLET_SHEET_GAP;
        rect[3]=4*BULLET_SHEET_GAP;
    }
    else
    {
        //左上角点
        int x1;
        int y1;
        if(want[0]<=4)
        {
            x1=(want[0]-1)*4*BULLET_SHEET_GAP;
            y1=(want[1]-1)*4*BULLET_SHEET_GAP;
        }
        else
        {
            x1=(want[0]-5)*4*BULLET_SHEET_GAP;
            y1=(want[1])*4*BULLET_SHEET_GAP;
        }
        //边长
        int x_side=4*BULLET_SHEET_GAP;
        int y_side=4*BULLET_SHEET_GAP;

        rect[0]=x1;
        rect[1]=y1;
        rect[2]=x_side;
        rect[3]=y_side;
    }

    return rect;
}