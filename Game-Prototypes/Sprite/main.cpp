#include <SFML/Graphics.hpp>
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    sf::Texture texture;
    texture.loadFromFile("colored_packed.png");
    sf::Sprite sprite,sprite1,sprite2,sprite3;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,16,16,16));
    sprite.setColor(sf::Color::White);
    sprite.setPosition(400,300);
    sprite.scale(10,10);
    sprite1.setTexture(texture);
    sprite1.setTextureRect(sf::IntRect(16,16,16,16));
    sprite1.setColor(sf::Color::White);
    sprite1.setPosition(0,0);
    sprite1.scale(10,10);
    sprite2.setTexture(texture);
    sprite2.setTextureRect(sf::IntRect(32,16,16,16));
    sprite2.setColor(sf::Color::White);
    sprite2.setPosition(400,0);
    sprite2.scale(10,10);
    sprite3.setTexture(texture);
    sprite3.setTextureRect(sf::IntRect(48,16,16,16));
    sprite3.setColor(sf::Color::White);
    sprite3.setPosition(640,0);
    sprite3.scale(10,10);

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
        window.draw(sprite);
        window.draw(sprite1);
        window.draw(sprite2);
        window.draw(sprite3);
        window.display();
    }

    return EXIT_SUCCESS;
}
