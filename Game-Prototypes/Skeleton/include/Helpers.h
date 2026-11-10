#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

struct StatusFlags
{
  bool gameplay;
  bool start_menu;
  bool pause_menu;
  bool settings_menu;
};

class AssetManager
{ 
  public:
    int tileWidth = 16;
    int tileHeight = 16;
    int totalTilesV = 11;
    int totalTilesH = 12;

    sf::Font font;
    sf::Texture tile_texture;
    sf::Texture character_texture;
    std::vector<sf::Sprite> tiles;
    std::vector<sf::Sprite> characters;

    AssetManager();

    void draw_tiles(sf::RenderWindow &window);
    void draw_characters(sf::RenderWindow &window);

    void load_tiles(std::string texture_name);
    void load_characters(std::string texture_name);
};
