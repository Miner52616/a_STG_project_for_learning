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