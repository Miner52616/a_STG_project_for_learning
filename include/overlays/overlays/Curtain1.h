#pragma once
#include "overlays/overlays/RecShape.h"

class Curtain1:public RecShape
{
public:
    Curtain1();
    void update() override;
    void render(sf::RenderWindow& window) override;
};