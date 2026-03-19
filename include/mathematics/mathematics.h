#pragma once
#include <SFML/Graphics.hpp>

float distancePointToSegment(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);

float getRandomNum(float a,float b);

int the_min(int a,int b);

sf::Vector2f roundwithCenter(sf::Vector2f center,sf::Vector2f point,float angle);

sf::Vector2f round(sf::Vector2f Vector,float angle);