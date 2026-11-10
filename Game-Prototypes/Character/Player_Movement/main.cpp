#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

struct Forageable{
  int mana;
  int hunger;
  int health;
  int stamina;
  std::string name;
  sf::RectangleShape sprite;
};

Forageable generate_default_berry()
{
  Forageable berry;

  berry.mana = 5;
  berry.hunger = 3;
  berry.health = 10;
  berry.stamina = 50;
  berry.name = "berry";
  berry.sprite.setPosition(200,300);
  berry.sprite.setOutlineThickness(2);
  berry.sprite.setSize(sf::Vector2f(16,16));
  berry.sprite.setFillColor(sf::Color::White);
  berry.sprite.setOutlineColor(sf::Color::White);

  return berry;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(800,600), "Window");
  window.setFramerateLimit(60);

  std::shared_ptr<Player> player = std::make_shared<Player>();

  Forageable berry;
  berry = generate_default_berry();

  player->sprite.setPosition(400,300);
  player->sprite.setOutlineThickness(5);
  player->sprite.setFillColor(sf::Color::Yellow);
  player->sprite.setSize(sf::Vector2f(32,32));
  player->sprite.setOutlineColor(sf::Color::Yellow);
  Movement m1 = {false,false,false,false,false};
  player->movement = std::make_shared<Movement>(m1);
  player->transform = std::make_shared<Transform>(generate_default_transform());

    // Game loop
  while (window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
      if(event.type == sf::Event::KeyPressed)
      {
        if(event.key.code == sf::Keyboard::Escape)
        {
          window.close();
        }
        if(event.key.code == sf::Keyboard::A)
        {
          player->movement->moving_left = true;
        }
        if(event.key.code == sf::Keyboard::D)
        {
          player->movement->moving_right = true;
        }
        if(event.key.code == sf::Keyboard::W)
        {
          player->movement->moving_up = true;
        }
        if(event.key.code == sf::Keyboard::S)
        {
          player->movement->moving_down = true;
        } 
      }
      if(event.type == sf::Event::KeyReleased)
      {
        if(event.key.code == sf::Keyboard::A)
        {
          player->movement->moving_left = false;
        }
        if(event.key.code == sf::Keyboard::D)
        {
          player->movement->moving_right = false;
        }
        if(event.key.code == sf::Keyboard::W)
        {
          player->movement->moving_up = false;
        }
        if(event.key.code == sf::Keyboard::S)
        {
          player->movement->moving_down = false;
        }
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      sf::Vector2f destination = {sf::Mouse::getPosition(window).x / 1.0f,sf::Mouse::getPosition(window).y / 1.0f};
      sWalk_to_destination(player,destination);
    }

    sMovement(player);
    
    window.clear(sf::Color::White);
    window.draw(player->sprite);
    window.display();
  }

  return EXIT_SUCCESS;
}
