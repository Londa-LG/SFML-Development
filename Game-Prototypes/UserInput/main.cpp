#include <SFML/Graphics.hpp>
#include <iostream>
 
// Event driven user input system

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Event driven input");
    int count = 0;

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
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if(event.key.code == sf::Keyboard::W)
                {
                    count++;
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::W)
                {
                    std::cout<< "count: " <<'\n';
                    count = 0;
                }
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    std::cout<< "Mouse position:" << '\n';
                    std::cout<< "x:" << x << '\n';
                    std::cout<< "y: " << y << '\n';
                }
            }
        }

        window.clear();
        window.display();
    }

    window.close();

    return EXIT_SUCCESS;
}
