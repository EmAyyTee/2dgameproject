#pragma once
#include <memory>

#include "Character.h"
#include "PlayerArrow.h"
#include "TextureLoader.h"
#include "SFML/Window/Keyboard.hpp"

class Player : public Character{

public:
    enum class PlayerState {
        PlayerIdle = 0,
        PlayerWalkingRight = 1,
        PlayerWalkingLeft = 2,
    };
    sf::Vector2f mousePosition;
    std::vector<PlayerArrow> *arrows;

    Player(const sf::Vector2f& position, std::shared_ptr<std::map<std::string, std::vector<std::pair <int, sf::Texture>>>> playerTexturesPointer,
        sf::RenderWindow* renderTarget, std::map<std::string, sf::Keyboard::Key> *supportedKeys);

    void update(float deltaTime,std::vector<PlayerArrow> &arrows);

    void playerGetInput();

    sf::Vector2f getPosition();

private:
    PlayerState playerState;
    std::shared_ptr<std::map<std::string, std::vector<std::pair <int, sf::Texture>>>> playerTexturesPointer;
    std::map<std::string, sf::Keyboard::Key>* supportedKeys;
    sf::Clock shotClock;
    float cooldownTimeForShootingAnArrow = 0.5f;
};
