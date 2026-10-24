#include "mathematics/mathematics.h"
#include "entities/Enemy.h"
#include <random>
#include <math.h>
#include <iostream>
#include <filesystem>
#include <system_error>
#include "mathematics/math_namespace.h"
#include "packages/Keys.h"

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

namespace stg_math
{
    std::mt19937 gen(std::random_device{}());
}

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

unsigned resetSeed(std::optional<unsigned> seed)
{
    unsigned current_seed;
    if(seed)
    {
        current_seed=*seed;
    }
    else
    {
        current_seed=std::random_device{}();
    }
    stg_math::gen.seed(current_seed);

    return current_seed;
}

float getRandomNum(float a,float b)
{
    if(a>b)
    {
        std::swap(a,b);
    }

    std::uniform_real_distribution<float> dis(a,b);

    return dis(stg_math::gen);
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

std::string numberToChinese(int number)
{
    const std::string chinese[]=
    {
        "〇", "一", "二", "三", "四",
        "五", "六", "七", "八", "九"
    };

    std::string numberString=std::to_string(number);
    std::string result;

    for (char c:numberString)
    {
        int digit=c-'0';
        result+=chinese[digit];
    }

    return result;
}

std::uint8_t encodeInput(const Keys& input)
{
    std::uint8_t bits = 0;

    if (input.key_Up_)     
    bits|=(1u<<0);
    if (input.key_Down_)   
    bits|=(1u<<1);
    if (input.key_Left_)   
    bits|=(1u<<2);
    if (input.key_Right_)  
    bits|=(1u<<3);
    if (input.key_LShift_) 
    bits|=(1u<<4);
    if (input.key_Z_)      
    bits|=(1u<<5);
    if (input.key_X_)      
    bits|=(1u<<6);

    return bits;
}

Keys decodeInput(std::uint8_t bits)
{
    Keys input;

    input.key_Up_=(bits&(1u << 0))!=0;
    input.key_Down_=(bits&(1u<<1))!=0;
    input.key_Left_=(bits&(1u<<2))!=0;
    input.key_Right_=(bits&(1u<<3))!=0;
    input.key_LShift_=(bits&(1u<<4))!=0;
    input.key_Z_=(bits&(1u<<5))!=0;
    input.key_X_=(bits&(1u<<6))!=0;

    return input;
}

bool writeU32(std::ostream& out, std::uint32_t value)
{
    for (int i = 0; i < 4; ++i)
    {
        const char byte = static_cast<char>(value & 0xFFu);

        out.put(byte);

        if (!out)
            return false;

        value >>= 8;
    }

    return true;
}

bool readU32(std::istream& in, std::uint32_t& value)
{
    value = 0;

    for (int i = 0; i < 4; ++i)
    {
        const auto ch = in.get();

        if (ch == std::char_traits<char>::eof())
            return false;

        const auto byte = static_cast<std::uint32_t>(
            static_cast<unsigned char>(ch)
        );

        value |= byte << (i * 8);
    }

    return true;
}

bool replaceReplayFile(const std::filesystem::path& temp_path,const std::filesystem::path& final_path)
{
#ifdef _WIN32
    // Windows：允许替换已经存在的正式文件。
    // 两个文件应当位于同一磁盘卷。
    return MoveFileExW(
        temp_path.c_str(),
        final_path.c_str(),
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH
    ) != 0;
#else
    // POSIX 系统：同一文件系统内，rename 可以原子替换目标文件。
    std::error_code ec;

    std::filesystem::rename(temp_path, final_path, ec);

    return !ec;
#endif
}