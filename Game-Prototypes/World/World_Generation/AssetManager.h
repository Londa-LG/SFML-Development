#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class AssetManager
{ 
  public:
    int tileWidth = 16;
    int tileHeight = 16;
    int totalTilesV = 22;
    int totalTilesH = 49;
    int totalTiles = 1078;

    sf::Texture texture;
    std::vector<sf::Sprite> tiles;

    AssetManager(std::string texture_name);
    void draw_tiles(sf::RenderWindow &window);
};
