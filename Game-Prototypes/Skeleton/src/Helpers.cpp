#include "Helpers.h"
#include <SFML/Graphics.hpp>


AssetManager::AssetManager()
{
  load_tiles("./assets/textures/world.png");
  load_characters("./assets/textures/character.png");
  font.loadFromFile("./assets/font/pixelfy_sans.ttf");
}

void AssetManager::load_characters(std::string texture_name)
{
  character_texture.loadFromFile(texture_name);
  
  for(int y=0; y<(totalTilesV * tileHeight); y += tileHeight)
  {
    for(int x=0; x<(totalTilesH * tileWidth);x += tileWidth)
    {
      sf::Sprite sp;
      sp.setTexture(character_texture);
      sp.setTextureRect(sf::IntRect(x,y,tileWidth,tileHeight));
      sp.setPosition(x,y);
      characters.push_back(sp);
    }
  }
}

void AssetManager::load_tiles(std::string texture_name)
{
  tile_texture.loadFromFile(texture_name);
  
  for(int y=0; y<(totalTilesV * tileHeight); y += tileHeight)
  {
    for(int x=0; x<(totalTilesH * tileWidth);x += tileWidth)
    {
      sf::Sprite sp;
      sp.setTexture(tile_texture);
      sp.setTextureRect(sf::IntRect(x,y,tileWidth,tileHeight));
      sp.setPosition(x,y);
      tiles.push_back(sp);
    }
  }
}

void AssetManager::draw_tiles(sf::RenderWindow &window)
{
  for(int i=0; i<tiles.size(); i++)
  {
    window.draw(tiles[i]);
  }
}

void AssetManager::draw_characters(sf::RenderWindow &window)
{
  for(int i=0; i<tiles.size(); i++)
  {
    window.draw(characters[i]);
  }
}


