#pragma once
#include "GreenSlime.h"

class SmallGreenSlime : public GreenSlime {
public:
    SmallGreenSlime(const sf::Vector2f &position, std::shared_ptr<std::vector<std::pair<int, sf::Texture> > > greenSlimeTexturesPointer, sf::RenderWindow *target);

    SmallGreenSlime() = default;
    ~SmallGreenSlime() = default;
};
