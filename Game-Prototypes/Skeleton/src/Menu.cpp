#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Helpers.h"
#include "Settings.h"

Button::Button()
{
}

Button::Button(AssetManager &am,std::string text,sf::Vector2f p_position,sf::Vector2f p_size)
{
  size = p_size;
  position = p_position;

  label.setFont(am.font);
  label.setString(text);
  label.setCharacterSize(18);
  label.setFillColor(sf::Color::Black);
  label.setPosition(position.x + 10,position.y - 2);

  button.setSize(size);
  button.setPosition(position);
  button.setOutlineThickness(4);
  button.setFillColor(sf::Color::Yellow);
  button.setOutlineColor(sf::Color::Yellow);
}

bool Button::detect_click(sf::RenderWindow &window)
{
  if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2f m_position = {sf::Mouse::getPosition(window).x/1.0f,sf::Mouse::getPosition(window).y/1.0f};

    if((m_position.x > position.x) && (m_position.x < (position.x + size.x)) && (m_position.y > position.y) && (m_position.y < (position.y + size.y)))
    {
      return true;
    }
  }

  return false;
}

void Button::draw(sf::RenderWindow &window)
{
  window.draw(button);
  window.draw(label);
}

StartMenu::StartMenu()
{
}

StartMenu::StartMenu(AssetManager &am,Settings &set)
{
  title.setFont(am.font);
  title.setString("Little Village");
  title.setCharacterSize(40);
  title.setStyle(sf::Text::Bold);
  title.setFillColor(sf::Color::Black);
  title.setPosition((set.width/2 - 150),(set.height/2 - 50));

  start_ins.setFont(am.font);
  start_ins.setString("Click Enter to start");

  start_ins.setCharacterSize(20);
  start_ins.setFillColor(sf::Color::Black);
  start_ins.setPosition((set.width/2 - 100),(set.height - 200));
}

void StartMenu::draw(sf::RenderWindow &window,StatusFlags &flags)
{
  if(flags.start_menu)
  {
    window.draw(title);
    window.draw(start_ins);
  }
}

void StartMenu::update(sf::Event &event,StatusFlags &flags)
{
  if(flags.start_menu)
  {
    if(event.type == sf::Event::KeyPressed)
    {
      if(event.key.code == sf::Keyboard::Enter)
        {
          flags.gameplay = true;
          flags.start_menu = false;
        }
    }
  }
}


PauseMenu::PauseMenu()
{
}

PauseMenu::PauseMenu(AssetManager &am,Settings &set)
{
  sf::Vector2f btn_size = {280,20};
  sf::Vector2f bg_size = {300,75};
  sf::Vector2f bg_position = {(set.width/2.0f - bg_size.x/2.0f),(set.height/2.0f - bg_size.y/2.0f)};

  background.setSize(bg_size);
  background.setOutlineThickness(4);
  background.setPosition(bg_position);
  background.setFillColor(sf::Color::Black);
  background.setOutlineColor(sf::Color::Black);

  btn_quit = Button(am,"Quit game",{bg_position.x + 10,bg_position.y + 45},btn_size);
  //btn_settings = Button(am,"Settings",{bg_position.x + 10,bg_position.y + 45},btn_size);
  btn_continue = Button(am,"Continue",{bg_position.x + 10,bg_position.y + 10},btn_size);
}

void PauseMenu::handle_quit(sf::RenderWindow &window)
{
  window.close();
}

void PauseMenu::handle_continue(StatusFlags &flags)
{
  flags.gameplay = true;
  flags.pause_menu = false;
}

/*void PauseMenu::handle_settings(StatusFlags &flags)
{
  flags.settings_menu = true;
  flags.pause_menu = false;
}*/

void PauseMenu::update(sf::Event &event,sf::RenderWindow &window,StatusFlags &flags)
{
  if(flags.pause_menu)
  {
    if(event.type == sf::Event::KeyPressed)
    {
      if(event.key.code == sf::Keyboard::Escape)
        {
          flags.gameplay = true;
          flags.pause_menu = false;
        }
    }
    if(btn_quit.detect_click(window))
    {
      handle_quit(window);
    }
    if(btn_continue.detect_click(window))
    {
      handle_continue(flags);
    }
    /*if(btn_settings.detect_click(window))
    {
      handle_settings(flags);
    }*/
  }
}

void PauseMenu::draw(sf::RenderWindow &window,StatusFlags &flags)
{
  if(flags.pause_menu)
  {
    window.draw(background);
    window.draw(btn_quit.button);
    window.draw(btn_quit.label);
    //btn_settings.draw(window);
    btn_continue.draw(window);
  }
}

/*
SettingsMenu()
{
}

SettingsMenu::SettingsMenu(AssetManager &am,Settings &set)
{
  sf::Vector2f btn_size = {280,20};
  sf::Vector2f bg_size = {300,115};
  full_screen = set.full_screen;

  sf::Vector2f bg_position = {(set.width/2.0f - bg_size.x/2.0f),(set.height/2.0f - bg_size.y/2.0f)};

  background.setSize(bg_size);
  background.setOutlineThickness(4);
  background.setPosition(bg_position);
  background.setFillColor(sf::Color::Black);
  background.setOutlineColor(sf::Color::Black);

  btn_save = Button(am,"Save",{},{});
  btn_full_screen = Button(am,"Window",{},{});
}

void SettingsMenu::draw(sf::RenderWindow &window,StatusFlags &flags)
{
  if(flags.settings_menu)
  {
    window.draw(background);
  }
}

void SettingsMenu::update(StatusFlags &flags)
{
  if(flags.settings_menu)
  {
  }
}
*/
