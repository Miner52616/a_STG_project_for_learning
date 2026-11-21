#include "core/LuaBindings.h"
#include <SFML/Graphics.hpp>

void registerSFMLBindings(sol::state& lua)
{
    lua.new_usertype<sf::Vector2f>
    (
        "Vector2f",
        sol::constructors<sf::Vector2f(float,float)>(),
        "x",&sf::Vector2f::x,
        "y",&sf::Vector2f::y
    );

    lua.new_usertype<sf::Vector2i>
    (
        "Vector2i",
        sol::constructors<sf::Vector2i(int,int)>(),
        "x",&sf::Vector2i::x,
        "y",&sf::Vector2i::y
    );

    lua.new_usertype<sf::Texture>
    (
        "Texture",
        sol::no_constructor
    );
}