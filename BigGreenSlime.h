#pragma once
#include <memory>

#include "GreenSlime.h"
#include "SFML/Graphics/RenderWindow.hpp"

class BigGreenSlime : public GreenSlime{
public:
    BigGreenSlime(const sf::Vector2f &position, std::shared_ptr<std::vector<std::pair<int, sf::Texture> > > greenSlimeTexturesPointer, sf::RenderWindow *target);

    BigGreenSlime() = default;
    ~BigGreenSlime() override = default;
};
