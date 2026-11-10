#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Helpers.h"
#include "Settings.h"
#include "Gameplay.h"

class Game
{
  public:
    AssetManager am;
    StartMenu start;
    PauseMenu pause;
    Gameplay gameplay;
    StatusFlags flags;
    Settings settings;
    sf::RenderWindow window;

    Game();
    void draw();
    void run();
};
