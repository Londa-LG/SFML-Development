#include <SFML/Graphics.hpp>
#include "Helpers.h"
#include "Gameplay.h"

Gameplay::Gameplay()
{
}

Gameplay::Gameplay(AssetManager &am)
{
  holder.setFont(am.font);
  holder.setString("Gameplay");
  holder.setCharacterSize(60);
  holder.setFillColor(sf::Color::Black);
  holder.setPosition(50,50);
}

void Gameplay::update(sf::Event &event,StatusFlags &flags)
{
  if((flags.gameplay) && (!flags.pause_menu))
  {
    if(event.type == sf::Event::KeyPressed)
    {
      if(event.key.code == sf::Keyboard::Escape)
      {
        flags.pause_menu = true;
      }
    }
  }
}

void Gameplay::draw(sf::RenderWindow &window,StatusFlags &flags)
{
  if(flags.gameplay)
  {
    window.draw(holder);
  }
}
