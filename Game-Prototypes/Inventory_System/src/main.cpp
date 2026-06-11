#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include "Player.h"
#include <memory>
#include <iostream>

class FileManager
{
    public:
        std::shared_ptr<sf::Font> font;
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<Inventory> inventory;
        std::shared_ptr<sf::Text> inventory_display;

        FileManager()
        {
            font = std::make_shared<sf::Font>();
            font->loadFromFile("assets/font/m5x7.ttf");

            texture = std::make_shared<sf::Texture>();
            texture->loadFromFile("assets/textures/player/Idle.png");

            inventory = std::make_shared<Inventory>();

            inventory_display = std::make_shared<sf::Text>();
            inventory_display->setFont(*font);
            inventory_display->setPosition(10,10);
            inventory_display->setCharacterSize(30);
            inventory_display->setString("Include:\n");
            inventory_display->setFillColor(sf::Color::Black);
        }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

    FileManager fm = FileManager();
/*    Inventory inv = Inventory();

    sf::Texture texture;
    texture.loadFromFile("assets/textures/player/Idle.png");

    sf::Font font;
    font.loadFromFile("assets/font/m5x7.ttf");

    sf::Text inventory_display("", font);
    inventory_display.setCharacterSize(30);
    inventory_display.setFillColor(sf::Color::Black);
    inventory_display.setPosition(10,10);

    std::shared_ptr<sf::Texture> player_texture;
    player_texture = std::make_shared<sf::Texture>(texture);
*/
    Player p1 = Player();
    player_init(p1,fm.texture);
    
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
        window.draw(*fm.inventory_display);
        window.draw(p1.sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}
