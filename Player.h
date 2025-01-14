#pragma once
#include <memory>

#include "Character.h"
#include "GameState.h"
#include "PlayerArrow.h"
#include "TextureLoader.h"
#include "SFML/Window/Keyboard.hpp"

class Player : public Character{

public:
    enum class PlayerState {
        PlayerIdle = 0,
        PlayerWalkingRight = 1,
        PlayerWalkingLeft = 2,
        PlayerHurt = 3,
        PlayerShootingRight = 4,
        PlayerShootingLeft = 5
    };
    sf::Vector2f mousePosition;
    std::vector<PlayerArrow> *arrows;
    int currentDamage;
    sf::RectangleShape detectionHitbox;
    sf::Clock shotClock;


    Player(const sf::Vector2f& position, std::shared_ptr<std::map<std::string, std::vector<std::pair <int, sf::Texture>>>> playerTexturesPointer,
        sf::RenderWindow* renderTarget, std::map<std::string, sf::Keyboard::Key> *supportedKeys);

    void update(float deltaTime,std::vector<PlayerArrow> &arrows);

    bool canAnimationCanChange();

    void playerGetInput();

    void draw(sf::RenderTarget &renderTarget);

    sf::Vector2f getPosition();

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
};
