#include "behaviors/behaviors/AimMove3.h"
#include "entities/Entity.h"
#include "effects/Effect.h"

AimMove3::AimMove3(std::variant<Effect*,Entity*> object,float v,sf::Vector2f targetposition):
    object_(object),v_(v),targetposition_(targetposition),nextposition_({0,0})
{
    ;
}

void AimMove3::update()
{
    std::visit
    (
        [this](auto object)
        {
            this->process_update(object);
        },
        object_
    );
}

void AimMove3::process_update(Effect* effect)
{
    effect->store_position();
    sf::Vector2f position=effect->getPosition();
    nextposition_=position+v_*(targetposition_-position);
    effect->setPosition(nextposition_);
}

void AimMove3::process_update(Entity* entity)
{
    entity->store_position();
    sf::Vector2f position=entity->getPosition();
    nextposition_=position+v_*(targetposition_-position);
    entity->setPosition(nextposition_);
}