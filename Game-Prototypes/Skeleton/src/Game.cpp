#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Helpers.h"
#include "Settings.h"
#include "Gameplay.h"
#include "Game.h"

Game::Game()
{
  init_settings(settings);

  window.create(sf::VideoMode(settings.width,settings.height),settings.title);
  window.setFramerateLimit(settings.frame_rate);

  flags.gameplay = false;
  flags.start_menu = true;
  flags.pause_menu = false;
  flags.settings_menu = false;

  am = AssetManager();
  start = StartMenu(am,settings);
  pause = PauseMenu(am,settings);
  gameplay = Gameplay(am);
}

void Game::run()
{
  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }

      start.update(event,flags);
      pause.update(event,window,flags);
      gameplay.update(event,flags);

      window.clear(sf::Color::White);
      start.draw(window,flags);
      pause.draw(window,flags);
      gameplay.draw(window,flags);
      window.display();
    }
  }
}

