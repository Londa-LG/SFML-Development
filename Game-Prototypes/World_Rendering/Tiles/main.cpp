#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

std::map<int,sf::IntRect> generateTileMap(int tileWidth,int tileHeight,std::string fileName)
{
    int tile = 0;
    sf::Texture texture;
    texture.loadFromFile(fileName);
    std::map<int,sf::IntRect> map;
    sf::Vector2u imageSize = texture.getSize();
    int colCount = imageSize.x / tileWidth;
    int rowCount = imageSize.y / tileHeight;

    for(int i=0; i!=rowCount; i++)
    {
        for(int j=0; j!=colCount; j++)
        {
            int x = tileWidth * j;
            int y = tileHeight * i;
            map[tile] = sf::IntRect(x,y,tileWidth,tileHeight);
            ++tile;
        }
    }

    return map;
}

std::vector<sf::Sprite> RenderLayer(std::shared_ptr<sf::Texture> texture,int width,int height,std::map<int,sf::IntRect> map,std::string fileName)
{
    int col = 0, row = 0;
    std::string line,value;
    std::ifstream file(fileName);
    std::vector<sf::Sprite> tiles;
    std::vector<sf::Vector2f> pos;

    while(file >> line)
    {
        std::istringstream data;
        data.str(line);
        while(std::getline(data,value,','))
        {
            sf::Sprite sprite;
            sprite.setTexture(*texture);
            sprite.setColor(sf::Color::White);
            sprite.setTextureRect(map[stoi(value)]);
            tiles.push_back(sprite);
        }
    }

    for(int i=0;i<=tiles.size();i++)
    {
        sf::Vector2f p1 = sf::Vector2f(col,row);
        pos.push_back(p1);
        col += 64;
        if(col == 640)
        {
            col = 0;
            row += 64;
        }
    }

    for(int i=0;i<=tiles.size();i++)
    {
        tiles[i].setPosition(pos[i]);
    }

    return tiles;
}

 
int main()
{
    sf::RenderWindow window(sf::VideoMode(640,640), "Map generation");
    window.setFramerateLimit(60);

    std::string fileName = "tiles/Tilemap_color1.png";
    const int width = 64, height = 64;
    std::map<int,sf::IntRect> map;
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(fileName);

    map = generateTileMap(width,height,fileName);

    std::vector<sf::Sprite> island = RenderLayer(texture,width,height,map,"csv/smallTopDown_Islands.csv");
    std::vector<sf::Sprite> clifs  = RenderLayer(texture,width,height,map,"csv/smallTopDown_clifs.csv");

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

        window.clear(sf::Color::Blue);
        for(int i=0; i!=island.size(); i++)
        {
            window.draw(island[i]);
        }
        for(int i=0; i!=clifs.size(); i++)
        {
            window.draw(clifs[i]);
        }

        window.display();

    }

    return EXIT_SUCCESS;
}
