#pragma once
#include <memory>

struct Transform{
  float maxVel;
  sf::Vector2f position;
  sf::Vector2f acceleration;
};

struct Movement{
  bool running;
  bool walking;
  bool moving_up;
  bool moving_down;
  bool moving_left;
  bool moving_right;
};

struct Player{
  bool moving;
  sf::RectangleShape sprite;
  std::shared_ptr<Movement> movement;
  std::shared_ptr<Transform> transform;
};

Transform generate_default_transform();
void sMovement(std::shared_ptr<Player> player);
void sWalk_to_destination(std::shared_ptr<Player> player,sf::Vector2f destination);
