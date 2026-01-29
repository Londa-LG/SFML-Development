#include <SFML/Graphics.hpp>

class Tile()
{
    float x;
    float y;
    float width;
    float height;
};

void sLoadMap()
{

}
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

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
        window.display();
    }

    return EXIT_SUCCESS;
}
