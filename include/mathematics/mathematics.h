#pragma once
#include <SFML/Graphics.hpp>

float distancePointToSegment(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);
float distancePointToSegment2(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);

float getRandomNum(float a,float b);

int the_min(int a,int b);

sf::Vector2f roundwithCenter(sf::Vector2f center,sf::Vector2f point,float angle);

sf::Vector2f round(sf::Vector2f Vector,float angle);

sf::Vector2f normalize(sf::Vector2f Vector);

sf::Vector2f get_randomposition_for_LeiTan(sf::Vector2f v);

long long int get_random_from(std::vector<long long int> vector);