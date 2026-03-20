#include "mathematics/mathematics.h"
#include <random>

float distancePointToSegment(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b)
{
    sf::Vector2f ab=b-a;
    sf::Vector2f ap=p-a;

    float t=ap.dot(ab)/ab.dot(ab);
    t=std::clamp(t,0.f,1.f);

    sf::Vector2f closest=a+(ab*t);
    return (p-closest).length();
}

float getRandomNum(float a,float b)
{
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

long long int get_random_from(std::vector<long long int> vector)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis_int(0,vector.size()-1);

    return vector[dis_int(gen)];
}