#include "packages/BulletConfig.h"

BulletConfig::BulletConfig(sf::Texture& texture):
    texture_(texture),clock1_(10),clock2_(0),clock3_(0)
{
    ;
}

void BulletConfig::setClock1(int target)
{
    clock1_.set_target(target);
    clock1_.reset();
}