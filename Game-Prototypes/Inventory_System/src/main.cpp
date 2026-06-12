#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include "Player.h"
#include <memory>
#include <iostream>

class FileManager
{
    public:
        std::shared_ptr<sf::Font> font;
        std::shared_ptr<sf::Texture> player_texture;
        std::shared_ptr<sf::Texture> icons;
        std::shared_ptr<Inventory> inventory;
        std::shared_ptr<sf::Text> inventory_display;

        FileManager()
        {
            font = std::make_shared<sf::Font>();
            font->loadFromFile("assets/font/m5x7.ttf");

            player_texture = std::make_shared<sf::Texture>();
            player_texture->loadFromFile("assets/textures/player/Idle.png");

            icons = std::make_shared<sf::Texture>();
            icons->loadFromFile("assets/textures/icons/Black_BG.png");

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
    Inventory inv;

    sf::Sprite ironSword,woodSword,steelSword;
    ironSword.setTexture(*fm.icons);
    woodSword.setTexture(*fm.icons);
    steelSword.setTexture(*fm.icons);
    ironSword.setTextureRect(sf::IntRect(32,160,32,32));
    woodSword.setTextureRect(sf::IntRect(0,160,32,32));
    steelSword.setTextureRect(sf::IntRect(64,160,32,32));
    woodSword.setPosition(80,10);
    ironSword.setPosition(120,10);
    steelSword.setPosition(160,10);
    Weapon w1 = {1,10,100,1000,true,5,"Wood sword",woodSword};
    Weapon w2 = {2,10,100,1000,true,5,"Iron sword",ironSword};
    Weapon w3 = {3,10,100,1000,true,5,"Steel sword",steelSword};
    collect_item_weapon(inv,w1);
    collect_item_weapon(inv,w2);
    collect_item_weapon(inv,w3);

    Player p1 = Player();
    player_init(p1,fm.player_texture);
    
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
        //Weapons
        window.draw(inv.weapons[1].sprite);
        window.draw(inv.weapons[2].sprite);
        window.draw(inv.weapons[3].sprite);
        window.draw(p1.sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}
