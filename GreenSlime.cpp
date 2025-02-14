#include "GreenSlime.h"

#include <fstream>
#include <iostream>

#include "fmt/format.h"

GreenSlime::GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer, sf::RenderWindow* target)
    : Character(position, target), greenSlimeTexturesPointer(std::move(greenSlimeTexturesPointer)) {
    hitPoints = 5;
    animation.calculateTheFrames(0,0,64,64);
    animation.setNumberOfFrames(6);
    direction = {0.0f, 0.0f};
    green_slime_animation = GreenSlimeAnimation::SlimeIdle;
    slimeSpeedModifier = 0.85;

    Character::setHitbox(sf::Vector2f{17.0f,15.0f}, sf::Color::Transparent, position, hitBox);
    Character::setHitbox(sf::Vector2f{664.0f,664.0f}, sf::Color::Transparent, position, detectionHitBox);
    Character::setHitbox(sf::Vector2f{64.0f,64.0f}, sf::Color::Transparent, position, attackHitbox);
    sprite.setScale(1.5f,1.5f);
    hitBox.setScale(1.2f,1.2f);
    attackHitbox.setScale(1.2f,1.2f);
    detectionHitBox.setScale(1.2f,1.2f);
}




void GreenSlime::update(float deltaTime, Player &player) {
    if (hitPoints <= 0) {
        isAlive = false;
        return;
    }
    checkForThePlayer(player);
    moveTowardsPlayer(player, deltaTime);
    checkForTheDamage(player);
    Character::update(deltaTime);
    Character::updateHitBox(hitBox);
    Character::updateHitBox(detectionHitBox);
    Character::updateHitBox(attackHitbox);
    animation.Update(deltaTime, static_cast<int>(green_slime_animation), sprite, greenSlimeTexturesPointer.get());
    // std::cout << "Slime positions is: " << position.x << " " << position.y << "\n";
}


void GreenSlime::checkForThePlayer(Player &player) {
    if (isAttacking) {
        position += directionalVector * speed * 1.0f/60.0f;
        if (animationClock.getClockTime().asSeconds() > animationTime) {
            green_slime_animation = GreenSlimeAnimation::SlimeIdle;
            isAnimationPlaying = false;
            isAttacking = false;
            animationClock.restart();
            atackCooldownClock.restart();
        }
    }
    if (player.getPlayerHitBox().getGlobalBounds().intersects(detectionHitBox.getGlobalBounds())|| attentionClock.getElapsedTime().asSeconds() > 10.0f) {
        green_slime_detection = GreenSlimeDetection::PlayerDetected;
    }
    if (player.getPlayerHitBox().getGlobalBounds().intersects(attackHitbox.getGlobalBounds())) {
        attack(player);
    }
    if (player.getHitBox().getGlobalBounds().intersects(hitBox.getGlobalBounds()) && isDealingDamage) {
        player.getDamage(greenSlimeDamage);
        damageClock.start();
        isDealingDamage = false;
    }
}

void GreenSlime::checkForTheDamage(Player &player) {
    for (PlayerArrow &arrow : *player.arrows) {
        if (arrow.getArrowHitBox().getGlobalBounds().intersects(hitBox.getGlobalBounds()) && getDamageClock.getElapsedTime().asSeconds() > 0.25f) {
            green_slime_detection = GreenSlimeDetection::PlayerDetected;
            hitPoints -= player.currentDamage;
            getDamageClock.restart();
            if (green_slime_animation != GreenSlimeAnimation::SlimeHurt) {
                green_slime_animation = GreenSlimeAnimation::SlimeHurt;
                isAnimationPlaying = true;
                animationClock.start();
                animationTime = 0.5f;
                animation.setHoldTime(0.1f);
                arrow.hp -= 1;
            }
        }
    }
    if (isAnimationPlaying && animationClock.getClockTime().asSeconds() > animationTime) {
        green_slime_animation = GreenSlimeAnimation::SlimeIdle;
        isAnimationPlaying = false;
        animationClock.restart();
    }
    if (!isDealingDamage && damageClock.getClockTime().asSeconds() > cooldownForDealingDamage) {
        isDealingDamage = true;
        damageClock.restart();
    }
}

void GreenSlime::normaliseVector(sf::Vector2f position) {
    directionalVector = position - this -> position;
    direction = {0.0f, 0.0f};

    //Vector normalisation formula

    magnitude = sqrt(directionalVector.x * directionalVector.x + directionalVector.y * directionalVector.y);
    directionalVector.x = directionalVector.x / magnitude;
    directionalVector.y = directionalVector.y / magnitude;
}


void GreenSlime::moveTowardsPlayer(Player &player, float deltaTime) {
    if (green_slime_detection == GreenSlimeDetection::PlayerDetected){
        if(!isAnimationPlaying) {
            normaliseVector(player.getPosition());
            chooseAnimation();
        }

        if (!player.getHitBox().getGlobalBounds().intersects(attackHitbox.getGlobalBounds()) && !isAnimationPlaying && atackCooldownClock.getElapsedTime().asSeconds() > 1.0f) {
            position += directionalVector * speed*slimeSpeedModifier * deltaTime;
        }
        else {
            if(!isAnimationPlaying) {
                green_slime_animation = GreenSlimeAnimation::SlimeIdle;
            }
        }
    }
}

void GreenSlime::chooseAnimation() {
    if (fabs(directionalVector.x) > fabs(directionalVector.y)) {
        if (directionalVector.x > 0.0f) {
            green_slime_animation = GreenSlimeAnimation::SlimeWalk;
            animation.calculateTheFrames(0,3,64,64);
        }
        else {
            green_slime_animation = GreenSlimeAnimation::SlimeWalk;
            animation.calculateTheFrames(0,2,64,64);
        }
    }
    else {
        if (directionalVector.y > 0.0f) {
            green_slime_animation = GreenSlimeAnimation::SlimeWalk;
            animation.calculateTheFrames(0,0,64,64);
        }
        else {
            green_slime_animation = GreenSlimeAnimation::SlimeWalk;
            animation.calculateTheFrames(0,1,64,64);
        }
    }
}

void GreenSlime::draw(sf::RenderTarget &renderTarget) {
    Character::draw(renderTarget);
    renderTarget.draw(detectionHitBox);
    renderTarget.draw(attackHitbox);
}

void GreenSlime::attack(Player &player) {
    if (atackCooldownClock.getElapsedTime().asSeconds() < cooldownForBeingAbleToAttack) {
        return;
    }
    if(!isAnimationPlaying && !isAttacking) {
        if (green_slime_animation != GreenSlimeAnimation::SlimeAttacking) {
            green_slime_animation = GreenSlimeAnimation::SlimeAttacking;
            isAnimationPlaying = true;
            targetBounds = player.getHitBox().getGlobalBounds();
            attackTargetPosition = {targetBounds.left, targetBounds.top};
            normaliseVector(attackTargetPosition);
            isAttacking = true;
            animationClock.start();
            animationTime = 1.0f;
            animation.setHoldTime(0.2f);
        }

    }

}

sf::Vector2f GreenSlime::getPosition() {
    return position;
}

void GreenSlime::setPosition(sf::Vector2f position) {
    this -> position = position;
}



void GreenSlime::saveToFile(std::ofstream &file) const{

    file.write(reinterpret_cast<const char*>(&position.x), sizeof(position.x));
    file.write(reinterpret_cast<const char*>(&position.y), sizeof(position.y));
    file.write(reinterpret_cast<const char*>(&hitPoints), sizeof(hitPoints));
    file.write(reinterpret_cast<const char*>(&slimeVariant), sizeof(slimeVariant));

}

void GreenSlime::loadFromFile(std::ifstream &file) {

    file.read(reinterpret_cast<char*>(&position.x), sizeof(position.x));
    file.read(reinterpret_cast<char*>(&position.y), sizeof(position.y));
    file.read(reinterpret_cast<char*>(&hitPoints), sizeof(hitPoints));
    file.read(reinterpret_cast<char*>(&slimeVariant), sizeof(slimeVariant));

    if(slimeVariant == 1) {
        sprite.setScale(4.0f, 4.0f);
        hitBox.setScale(4.0f, 4.0f);
        slimeSpeedModifier = 0.65f;
        hitBox.setScale(3.8f,3.8);
        attackHitbox.setScale(1.2f,1.2);
        detectionHitBox.setScale(2.0f,2.0f);
        greenSlimeDamage = 5;
    } else if(slimeVariant == 2) {
        sprite.setScale(0.75, 0.75f);
        hitBox.setScale(0.75f, 0.75f);
        slimeSpeedModifier = 1.2f;
        hitBox.setScale(0.75f,0.75f);
        attackHitbox.setScale(0.75f,0.75f);
        detectionHitBox.setScale(2.0f,2.0f);
        greenSlimeDamage = 1;
    }

}
