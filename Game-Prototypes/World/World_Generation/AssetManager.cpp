#include <SFML/Graphics.hpp>
#include "AssetManager.h"

AssetManager::AssetManager(std::string texture_name)
{
  texture.loadFromFile(texture_name);
  
  for(int y=0; y<(totalTilesV * tileHeight); y += tileHeight)
  {
    for(int x=0; x<(totalTilesH * tileWidth);x += tileWidth)
    {
      sf::Sprite sp;
      sp.setTexture(texture);
      sp.setTextureRect(sf::IntRect(x,y,16,16));
      sp.setPosition(x,y);
      tiles.push_back(sp);
    }
  }
}

void AssetManager::draw_tiles(sf::RenderWindow &window)
{
  int index = 0;
  for(int i=0; i<tiles.size(); i++)
  {
    window.draw(tiles[i]);
  }
  index++;
};
