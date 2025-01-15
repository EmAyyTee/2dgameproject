#pragma once
#include <memory>

#include "Character.h"
#include "GameState.h"
#include "PlayerArrow.h"
#include "TextureLoader.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Keyboard.hpp"

class Player : public Character{

public:
    enum class PlayerState {
        PlayerIdle = 0,
        PlayerWalkingRight = 1,
        PlayerWalkingLeft = 2,
        PlayerHurt = 3,
        PlayerDashingRight = 4,
        PlayerDashingLeft = 5,
        PlayerShootingRight = 6,
        PlayerShootingLeft = 7
    };
    sf::Vector2f mousePosition;
    std::vector<PlayerArrow> *arrows;
    int currentDamage;
    float speedModifier = 1.0f;
    sf::Vector2f tempDirection = {0.0f,0.0f};
    sf::RectangleShape detectionHitbox;
    sf::Clock shotClock;
    sf::Clock dashClock;
    int score = 0;
    int arrowsHp;
    bool isShooting = false;

    //Level logic
    int playerLevel = 1;
    int upgradesCount = 1;
    int playerPiercingLevel = 1;
    int playerDamageLevel = 1;
    int playerSpeedLevel = 1;
    int playerHealthLevel = 1;
    int playerDashAbility = 1;
    bool canThePlayerLevelUp();

    //Level logic


    Player(const sf::Vector2f& position, std::shared_ptr<std::map<std::string, std::vector<std::pair <int, sf::Texture>>>> playerTexturesPointer,
        sf::RenderWindow* renderTarget, std::map<std::string, sf::Keyboard::Key> *supportedKeys);

    void update(float deltaTime,std::vector<PlayerArrow> &arrows);

    bool canAnimationCanChange();

    void playerGetInput();

    void draw(sf::RenderTarget &renderTarget);

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f position);


    void addToScore(int points);

    sf::RectangleShape getPlayerHitBox();

    void getDamage(int damage);

    void saveToFile(std::ofstream &file);

    void loadFromFile(std::ifstream& file);


private:
    PlayerState playerState;
    std::shared_ptr<std::map<std::string, std::vector<std::pair <int, sf::Texture>>>> playerTexturesPointer;
    std::map<std::string, sf::Keyboard::Key>* supportedKeys;
    bool isHurt = false;

    float cooldownTimeForShootingAnArrow = 0.5f;
    float cooldownTimeForDashing = 5.0f;
};
