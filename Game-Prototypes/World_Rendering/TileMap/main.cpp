#include <SFML/Graphics.hpp>
#include <iostream>

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

void displayTiles(sf::RenderWindow& window,std::map<int,sf::IntRect> map,std::string textureFile)
{
    sf::Texture texture;
    texture.loadFromFile(textureFile);

    for(int i=0; i!=map.size(); i++)
    {
        sf::Sprite s1;
        s1.setTexture(texture);
        s1.setTextureRect(map[i]);
        s1.setColor(sf::Color::White);
        s1.setPosition(map[i].left,map[i].top);
        window.draw(s1);
    }
}
 
int main()
{
    int tileWidth = 16;
    int tileHeight = 16;
    std::string textureFile = "Terrain.png";

    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

    std::map<int,sf::IntRect> map = generateTileMap(tileWidth,tileHeight,textureFile);

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

        window.clear(sf::Color::Yellow);
        displayTiles(window,map,textureFile);
        window.display();
    }



    return EXIT_SUCCESS;
}
