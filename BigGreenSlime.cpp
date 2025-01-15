#include "BigGreenSlime.h"

#include "GreenSlime.h"

BigGreenSlime::BigGreenSlime(const sf::Vector2f &position, std::shared_ptr<std::vector<std::pair<int, sf::Texture> > > greenSlimeTexturesPointer, sf::RenderWindow *target)
    :GreenSlime(position, greenSlimeTexturesPointer, target){

    sprite.setScale(4.0f, 4.0f);
    hitBox.setScale(4.0f, 4.0f);
    hitPoints = 20;
    slimeSpeedModifier = 0.65f;
    hitBox.setScale(3.8f,3.8);
    attackHitbox.setScale(1.2f,1.2);
    detectionHitBox.setScale(2.0f,2.0f);
    greenSlimeDamage = 8;
    slimeVariant = 1;
}

