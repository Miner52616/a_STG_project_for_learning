#include "lua_packages/LuaEntity.h"
#include "entities/Entity.h"

LuaEntity::LuaEntity(Entity* entity):
    entity_(entity)
{
    ;
}

sf::Vector2f LuaEntity::getPosition()
{
    return entity_->getPosition();
}