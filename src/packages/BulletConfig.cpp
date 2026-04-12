#include "packages/BulletConfig.h"

BulletConfig::BulletConfig(sf::Texture& texture):
    texture_(texture),clock1_(10)
{
    ;
}

void BulletConfig::setClock1(int target)
{
    clock1_.set_target(target);
    clock1_.reset();
}