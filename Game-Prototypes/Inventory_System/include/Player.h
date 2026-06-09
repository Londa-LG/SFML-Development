#pragma once
#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include <memory>

struct Player{
    Inventory inventory;
    sf::Sprite sprite;
    sf::FloatRect position;
    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;
};

void player_init(Player &player,std::shared_ptr<sf::Texture> texture);
void player_move(Player &player);

