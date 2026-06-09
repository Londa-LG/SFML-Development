#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include "Player.h"
#include <memory>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("assets/textures/player/Idle.png");

    std::shared_ptr<sf::Texture> player_texture;
    player_texture = std::make_shared<sf::Texture>(texture);

    Player p1 = Player();
    player_init(p1,player_texture);
    
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
        window.draw(p1.sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}
