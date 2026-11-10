#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class cBoundingBox
{
    public:
        float top;
        float left;
        float right;
        float bottom;

        float width;
        float height;

        sf::Vector2f currentPosition = sf::Vector2f(0,0);
        sf::Vector2f previousPosition = sf::Vector2f(0,0);

    cBoundingBox(){}

    cBoundingBox(float x,float y,float pWidth,float pHeight)
    {
        top = y;
        left = x;
        width = pWidth;
        height = pHeight;
        right = x + width;
        bottom = y + height;
        currentPosition = sf::Vector2f(x,y);
        previousPosition = sf::Vector2f(x,y);
    }
    void updateBox(float x,float y,float pWidth,float pHeight)
    {
        top = y;
        left = x;
        width = pWidth;
        height = pHeight;
        right = x + width;
        bottom = y + height;
        currentPosition = sf::Vector2f(x,y);
        previousPosition = sf::Vector2f(x,y);
    }
    void updatePosition(sf::Vector2f pos)
    {
        top = pos.y;
        left = pos.x;
        right = pos.x + width;
        bottom = pos.y + height;

        previousPosition = currentPosition;
        currentPosition = pos;
    }
};

struct Movement
{
    bool jump = false;
    bool fall = false;
    bool left = false;
    bool right = false;
    float speed = 1600;
    float jumpDestination;
    float jumpHeight = 50;
};

struct Transform
{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

struct Tile
{
    cBoundingBox rect;
    sf::Sprite tileSprite;
};

struct DynamicTile
{
    cBoundingBox rect;
    Transform transform;
    sf::Sprite tileSprite;
};

class LevelGenerator
{
    sf::Texture texture;
    std::vector<Tile> tiles;
    std::vector<std::string> levels;
    std::map<int,sf::IntRect> tileMap;
    //std::vector<DynamicTile> dynamicTiles;

    public:
    int currentLevel;

    LevelGenerator(int tileWidth,int tileHeight, std::string textureName,std::vector<std::string> pLevels)
    {
        levels = pLevels;
        texture.loadFromFile(textureName);
        generateTileMap(tileWidth,tileHeight);
    }

    void generateTileMap(int tileWidth,int tileHeight)
    {
        int tile = 0;
        sf::Vector2u imageSize = texture.getSize();
        int colCount = imageSize.x / tileWidth;
        int rowCount = imageSize.y / tileHeight;

        for(int i=0; i!=rowCount; i++)
        {
            for(int j=0; j!=colCount; j++)
            {
                int x = tileWidth * j;
                int y = tileHeight * i;
                tileMap[tile] = sf::IntRect(x,y,tileWidth,tileHeight);
                ++tile;
            }
        }
    }
    void generateTiles(int colCount,float tileWidth,float tileHeight)
    {
        float col = 0, row = 0;
        std::string line, value;
        std::ifstream file(levels[currentLevel]);
        std::vector<sf::Vector2f> pos;

        while(file >> line)
        {
            std::istringstream data;
            data.str(line);
            while(std::getline(data,value,','))
            {
                if(stoi(value) >= 1)
                {
                    Tile tile;
                    tile.tileSprite.setTexture(texture);
                    tile.tileSprite.setColor(sf::Color::White);
                    tile.tileSprite.setTextureRect(tileMap[stoi(value)]);
                    tile.rect.updateBox(col,row,tileWidth,tileHeight);
                    tile.tileSprite.setPosition(sf::Vector2f(col,row));
                    tiles.push_back(tile);
                }
                col += tileWidth;
                if(col == (tileWidth * colCount))
                {
                    col = 0;
                    row += tileHeight;
                }
            }
        }
    }
    void drawLevel(sf::RenderWindow& window)
    {
        for(int i=0; i<tiles.size(); i++)
        {
            window.draw(tiles[i].tileSprite);
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(650,400), "Window");
    window.setFramerateLimit(60);

    std::vector<std::string> levels = {"./csv/level_1.csv","./csv/level_2.csv","./csv/level_3.csv","./csv/level_4.csv","./csv/level_5.csv"};
    LevelGenerator level = LevelGenerator(16,16,"./Terrain.png",levels);
    level.generateTiles(40,16.f,16.f);

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

        window.clear(sf::Color::White);
        level.drawLevel(window);
        window.display();
    }

    return EXIT_SUCCESS;
}



















































