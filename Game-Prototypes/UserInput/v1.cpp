#include <SFML/Graphics.hpp>
#include <iostream>
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(1200,600), "Window");

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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            std::cout<< "Left arrow pressed" << '\n';
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            std::cout<< "Right arrow pressed" << '\n';
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            std::cout<< "W pressed" << '\n';
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition();
            std::cout<< "Mouse position: " << '\n';
            std::cout<< "x:" << mousePosition.x << '\n';
            std::cout<< "y:" << mousePosition.y << '\n';
        }

        window.clear(sf::Color::Transparent);
        window.display();
    }

    window.close();
    return EXIT_SUCCESS;
}
