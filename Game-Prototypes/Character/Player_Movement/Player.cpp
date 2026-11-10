#include <SFML/Graphics.hpp>
#include "Player.h"
#include <math.h>
#include <iostream>

void sMovement(std::shared_ptr<Player> player){
  if((player->movement->moving_left) && (player->movement->moving_up == false) && (player->movement->moving_down == false))
  {
    player->transform->position.x -= player->transform->acceleration.x;
    player->sprite.setPosition(player->transform->position);
  }
  else if((player->movement->moving_right) && (player->movement->moving_up == false) && (player->movement->moving_down == false))
  {
    player->transform->position.x += player->transform->acceleration.x;
    player->sprite.setPosition(player->transform->position);
  }

  if((player->movement->moving_up) && (player->movement->moving_left == false) && (player->movement->moving_right == false))
  {
    player->transform->position.y -= player->transform->acceleration.y;
    player->sprite.setPosition(player->transform->position);
  }
  else if((player->movement->moving_down) && (player->movement->moving_left == false) && (player->movement->moving_right == false))
  {
    player->transform->position.y += player->transform->acceleration.y;
    player->sprite.setPosition(player->transform->position);
  }
}

void sWalk_to_destination(std::shared_ptr<Player> player,sf::Vector2f destination)
{

  if((destination.y > player->sprite.getPosition().y) && ((destination.y - player->sprite.getPosition().y) >= player->transform->acceleration.y))
  {
    player->transform->position.y += player->transform->acceleration.y;
    player->sprite.setPosition(player->transform->position);

    return;
  }
  else if(destination.y < player->sprite.getPosition().y && ((player->sprite.getPosition().y - destination.y) >= player->transform->acceleration.y))
  {
    player->transform->position.y -= player->transform->acceleration.y;
    player->sprite.setPosition(player->transform->position);
    return;
  }
  
  if(destination.x > player->sprite.getPosition().x && ((destination.x - player->sprite.getPosition().x) >= player->transform->acceleration.x))
  {
    player->transform->position.x += player->transform->acceleration.x;
    player->sprite.setPosition(player->transform->position);
    return;
  }
  else if(destination.x < player->sprite.getPosition().x && ((player->sprite.getPosition().x - destination.x) >= player->transform->acceleration.x))
  {
    player->transform->position.x -= player->transform->acceleration.x;
    player->sprite.setPosition(player->transform->position);
    return;
  }
}

Transform generate_default_transform(){
  Transform trn;
  float mov_pix = 2;
  float mov_seconds = 1;
  trn.position = {400,300};

  trn.maxVel = mov_pix / (0.5 * mov_seconds);
  trn.acceleration.x = pow(trn.maxVel,2) / (2*mov_pix);
  trn.acceleration.y = pow(trn.maxVel,2) / (2*mov_pix);
  
  return trn;
}
