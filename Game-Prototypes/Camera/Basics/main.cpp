#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

std::vector<sf::Sprite> generateMapLayer(std::shared_ptr<sf::Texture> texture,int width,int height,std::map<std::string,sf::IntRect> map,std::string fileName)
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
            sprite.setTextureRect(map[value]);
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

    const int width = 64, height = 64;
    std::map<std::string,sf::IntRect> map;
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("Tilemap_color1.png");

    // write out map
    map["0"] = sf::IntRect(0,0,width,height);
    map["1"] = sf::IntRect(64,0,width,height);
    map["2"] = sf::IntRect(128,0,width,height);
    map["3"] = sf::IntRect(192,0,width,height);
    map["5"] = sf::IntRect(320,0,width,height);
    map["6"] = sf::IntRect(384,0,width,height);
    map["7"] = sf::IntRect(448,0,width,height);
    map["8"] = sf::IntRect(512,0,width,height);
    map["9"] = sf::IntRect(0,64,width,height);
    map["10"] = sf::IntRect(64,64,width,height);
    map["11"] = sf::IntRect(128,64,width,height);
    map["12"] = sf::IntRect(193,64,width,height);
    map["14"] = sf::IntRect(320,64,width,height);
    map["15"] = sf::IntRect(384,64,width,height);
    map["16"] = sf::IntRect(448,64,width,height);
    map["17"] = sf::IntRect(512,64,width,height);
    map["18"] = sf::IntRect(0,128,width,height);
    map["19"] = sf::IntRect(64,128,width,height);
    map["20"] = sf::IntRect(128,128,width,height);
    map["21"] = sf::IntRect(192,128,width,height);
    map["23"] = sf::IntRect(320,128,width,height);
    map["24"] = sf::IntRect(384,128,width,height);
    map["25"] = sf::IntRect(448,128,width,height);
    map["26"] = sf::IntRect(512,128,width,height);
    map["27"] = sf::IntRect(0,192,width,height);
    map["28"] = sf::IntRect(64,192,width,height);
    map["29"] = sf::IntRect(128,192,width,height);
    map["30"] = sf::IntRect(192,192,width,height);
    map["32"] = sf::IntRect(320,192,width,height);
    map["33"] = sf::IntRect(384,192,width,height);
    map["34"] = sf::IntRect(448,192,width,height);
    map["35"] = sf::IntRect(512,192,width,height);
    map["36"] = sf::IntRect(0,256,width,height);
    map["39"] = sf::IntRect(192,256,width,height);
    map["41"] = sf::IntRect(320,256,width,height);
    map["42"] = sf::IntRect(384,256,width,height);
    map["43"] = sf::IntRect(448,256,width,height);
    map["44"] = sf::IntRect(512,256,width,height);
    map["45"] = sf::IntRect(0,320,width,height);
    map["48"] = sf::IntRect(192,320,width,height);
    map["50"] = sf::IntRect(320,320,width,height);
    map["51"] = sf::IntRect(384,320,width,height);
    map["52"] = sf::IntRect(448,320,width,height);
    map["53"] = sf::IntRect(512,320,width,height);

    std::vector<sf::Sprite> island = generateMapLayer(texture,width,height,map,"smallTopDown_Islands.csv");
    std::vector<sf::Sprite> clifs  = generateMapLayer(texture,width,height,map,"smallTopDown_clifs.csv");

    // Camera
    sf::View view;
    view.reset(sf::FloatRect(100,100,400,200));
    view.setViewport(sf::FloatRect(0.f,0.f,0.5f,1.f));

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
