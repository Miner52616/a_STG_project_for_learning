#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <string>

class Keys;

class Two_Vector2i
{
public:
    sf::Vector2i vec1_={0,0};
    sf::Vector2i vec2_={0,0};
};

float distancePointToSegment(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);
float distancePointToSegment2(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);

unsigned resetSeed(std::optional<unsigned> seed=std::nullopt);
float getRandomNum(float a,float b);

int the_min(int a,int b);

int round_off(float num);

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

Two_Vector2i bulletsheet_transform(const sf::Vector2i& want);
Two_Vector2i big_bulletsheet_transform(const sf::Vector2i& want);
Two_Vector2i large_bulletsheet_transform(const sf::Vector2i& want);
Two_Vector2i playersheet_bullet_transform(const sf::Vector2i& want);
Two_Vector2i playersheet_effect_transform(const sf::Vector2i& want);
Two_Vector2i effectsheet_transform(const sf::Vector2i& want);

std::string numberToChinese(int number);

std::uint8_t encodeInput(const Keys& input);
Keys decodeInput(std::uint8_t bits);

bool writeU32(std::ostream& out, std::uint32_t value);
bool readU32(std::istream& in, std::uint32_t& value);

bool replaceReplayFile(const std::filesystem::path& temp_path,const std::filesystem::path& final_path);

#include "mathematics/mathematics.ipp"