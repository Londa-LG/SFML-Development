#include <SFML/Graphics.hpp>
#include "Player.h"
#include <memory>


void player_init(Player &player,std::shared_ptr<sf::Texture> texture)
{
    player.sprite.setTexture(*texture);
    player.sprite.setTextureRect(sf::IntRect(0,0,32,32));
    player.sprite.setColor(sf::Color::White);
    player.position = sf::FloatRect(300,400,32,32);
    player.sprite.setPosition(player.position.top,player.position.left);
}

void player_move(Player &player)
{
}
