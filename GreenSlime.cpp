#include "GreenSlime.h"
#include <iostream>

#include "fmt/format.h"

GreenSlime::GreenSlime(const sf::Vector2f& position, std::shared_ptr<std::vector<std::pair <int, sf::Texture>>> greenSlimeTexturesPointer, sf::RenderWindow* target)
    : Character(position, target), greenSlimeTexturesPointer(std::move(greenSlimeTexturesPointer)) {
    hitPoints = 5;
    animation.calculateTheFrames(0,0,64,64);
    animation.setNumberOfFrames(6);
    direction = {0.0f, 0.0f};
    green_slime_animation = GreenSlimeAnimation::SlimeIdle;

    Character::setHitbox(sf::Vector2f{17.0f,15.0f}, sf::Color::Transparent, position, hitBox);
    Character::setHitbox(sf::Vector2f{664.0f,664.0f}, sf::Color::Transparent, position, detectionHitBox);
    Character::setHitbox(sf::Vector2f{64.0f,64.0f}, sf::Color::Transparent, position, attackHitbox);
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
    if (player.getPlayerHitBox().getGlobalBounds().intersects(detectionHitBox.getGlobalBounds())) {
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
        if (arrow.getArrowHitBox().getGlobalBounds().intersects(hitBox.getGlobalBounds())) {
            green_slime_detection = GreenSlimeDetection::PlayerDetected;
            hitPoints -= player.currentDamage;
            if (green_slime_animation != GreenSlimeAnimation::SlimeHurt) {
                green_slime_animation = GreenSlimeAnimation::SlimeHurt;
                isAnimationPlaying = true;
                animationClock.start();
                animationTime = 0.5f;
                animation.setHoldTime(0.1f);
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

        if (!player.getHitBox().getGlobalBounds().intersects(attackHitbox.getGlobalBounds()) && !isAnimationPlaying) {
            position += directionalVector * speed*0.75f * deltaTime;
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
