#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

float distancePointToSegment(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);
float distancePointToSegment2(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);

float getRandomNum(float a,float b);

int the_min(int a,int b);

sf::Vector2f roundwithCenter(sf::Vector2f center,sf::Vector2f point,float angle);

sf::Vector2f round(sf::Vector2f Vector,float angle);

sf::Vector2f normalize(sf::Vector2f Vector);

sf::Vector2f get_randomposition_for_LeiTan(sf::Vector2f v);

/*
long long int get_random_from(std::vector<long long int> vector);

int get_random_from(std::vector<int> vector);
*/

template <typename T>
T get_random_from(std::vector<T> vector);

float RadTransToDegree(float rad);

constexpr int BULLET_SHEET_GAP=16;

std::vector<int> bulletsheet_transform(const std::vector<int>& want);
std::vector<int> big_bulletsheet_transform(const std::vector<int>& want);
std::vector<int> large_bulletsheet_transform(const std::vector<int>& want);
std::vector<int> playersheet_bullet_transform(const std::vector<int>& want);
std::vector<int> playersheet_effect_transform(const std::vector<int>& want);
std::vector<int> effectsheet_transform(const std::vector<int>& want);

#include "mathematics/mathematics.ipp"