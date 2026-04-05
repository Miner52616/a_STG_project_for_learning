#include "behaviors/behaviors/DirectMove1.h"
#include "mathematics/mathematics.h"
#include "entities/Entity.h"

DirectMove1::DirectMove1(Entity* entity,float v,sf::Vector2f direction):
    entity_(entity),v_(v)
{
    direction_=normalize(direction);
}

void DirectMove1::update()
{
    entity_->setPosition(entity_->getPosition()+v_*direction_);
}