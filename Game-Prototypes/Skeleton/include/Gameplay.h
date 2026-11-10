#pragma once
#include <SFML/Graphics.hpp>
#include "Helpers.h"

class Gameplay
{
  public:
    sf::Text holder;

    Gameplay();
    Gameplay(AssetManager &am);
    void update(sf::Event &event,StatusFlags &flags);
    void draw(sf::RenderWindow &window,StatusFlags &flags);
};
