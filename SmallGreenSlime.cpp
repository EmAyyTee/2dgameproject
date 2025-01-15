#include "SmallGreenSlime.h"

SmallGreenSlime::SmallGreenSlime(const sf::Vector2f &position,
    std::shared_ptr<std::vector<std::pair<int, sf::Texture> > > greenSlimeTexturesPointer,
    sf::RenderWindow *target) :GreenSlime(position, greenSlimeTexturesPointer, target){

        sprite.setScale(0.75, 0.75f);
        hitBox.setScale(0.75f, 0.75f);
        hitPoints = 1;
        slimeSpeedModifier = 1.2f;
        hitBox.setScale(0.75f,0.75f);
        attackHitbox.setScale(0.75f,0.75f);
        detectionHitBox.setScale(2.0f,2.0f);
        greenSlimeDamage = 1;
        slimeVariant = 2;
}
