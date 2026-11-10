#pragma once
#include <SFML/Graphics.hpp>
#include "Helpers.h"
#include "Settings.h"

class Button
{
  public:
    sf::Text label;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::RectangleShape button;

    Button();
    Button(AssetManager &am,std::string text,sf::Vector2f p_position,sf::Vector2f p_size);

    bool detect_click(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
};

class StartMenu
{
  public:
    sf::Text title;
    sf::Text start_ins;

    StartMenu();
    StartMenu(AssetManager &am,Settings &set);

    void draw(sf::RenderWindow &window,StatusFlags &flags);
    void update(sf::Event &event,StatusFlags &flags);
};

class PauseMenu
{
  public:
    Button btn_quit;
    Button btn_continue;
    Button btn_settings;
    sf::RectangleShape background;

    PauseMenu();
    PauseMenu(AssetManager &am,Settings &set);

    void handle_continue(StatusFlags &flags);
    void handle_settings(StatusFlags &flags);
    void handle_quit(sf::RenderWindow &window);
    void update(sf::Event &event,sf::RenderWindow &window,StatusFlags &flags);
    void draw(sf::RenderWindow &window,StatusFlags &flags);
};

class SettingsMenu
{
  public:
    Button btn_save;
    bool full_screen;
    Button btn_apply;
    sf::RectangleShape background;

    SettingsMenu();
    SettingsMenu(Settings &set);

    void update(StatusFlags &flags);
    void draw(sf::RenderWindow &window);
    void save(StatusFlags &flags,Settings &set);
};
