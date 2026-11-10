#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include "AssetManager.h"

/* To do */
// Use asset manager to generate world

struct Mapping{
  int id;
  int row;
  int column;
};


class Layer
{
  public:
    int tile_size = 16;
    int total_rows = 23;
    int total_columns = 39;
    int total_tiles = 1078;
    std::vector<Mapping> level_tiles;

    Layer(std::string filename)
    {
      std::ifstream file(filename);
      std::string row ,numb;

      int row_index =0;
      int column_index = 0;
      while(file >> row)
      {
        int start= 0;
        for(int i=0; i<row.length(); i++)
        {
          if(row.at(i) == ',')
          {
            for(int j=start; j<i; j++)
            {
              numb += row.at(j);
            }

            Mapping m1;
            m1.column = column_index * tile_size;
            m1.row = row_index * tile_size;
            m1.id = std::stoi(numb);
            level_tiles.push_back(m1);

            numb.clear();
            start = i + 1;
            column_index++;
          }
        }
        row_index++;
        column_index = 0;
      }

      file.close();

    }

    void detect_transform(int raw)
    {
      // For handling Tiled id system
      // Id's have rotation incoded in them
      uint32_t rawGid = raw;

      bool flipH = (rawGid & 0x80000000) != 0;
      bool flipV = (rawGid & 0x40000000) != 0;
      bool flipD = (rawGid & 0x20000000) != 0;

      uint32_t tileGid = rawGid & 0x1FFFFFFF;
    }

    int remove_rotation(int raw)
    {
      // Getting Raw tile id
      uint32_t tileGid = raw & 0x1FFFFFFF;
      return tileGid;
    }

    void draw(std::vector<sf::Sprite> &tiles,sf::RenderWindow &window)
    {
      int index;
      for(int i=0; i<level_tiles.size(); i++)
      {
        Mapping m = level_tiles[i];
        if((m.id > 0) && (m.id < total_tiles)){
          sf::Sprite tile = tiles[m.id];
          tile.setPosition(m.column,m.row);
          window.draw(tile);
        }
        else if(m.id > 0){
          int id = remove_rotation(m.id);
          sf::Sprite tile = tiles[id];
          tile.setPosition(m.column,m.row);
          window.draw(tile);
        }
      }
    }
};
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "World generation V2");
    window.setFramerateLimit(60);

    // Load texture
    AssetManager am = AssetManager("colored-transparent_packed.png");
    Layer objects = Layer("sample_world_Objects.csv");
    Layer ground = Layer("sample_world_Ground.csv");

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        ground.draw(am.tiles,window);
        objects.draw(am.tiles,window);
        window.display();
    }

    return EXIT_SUCCESS;
}
