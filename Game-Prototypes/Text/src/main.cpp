#include <SFML/Graphics.hpp>
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

    // Text
    sf::Font font;
    font.loadFromFile("assets/font/m5x7.ttf");

    sf::Text text("Hello world", font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10,10);


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
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}
