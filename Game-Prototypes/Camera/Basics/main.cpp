#include <SFML/Graphics.hpp>
#include <iostream>
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(640,640), "Camera");
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("Tilemap_color1.png");
    sf::Sprite bg;
    bg.setTexture(texture);
    bg.setScale(2000.f/texture.getSize().x,2000.f/texture.getSize().y);

    // Camera
    sf::View view,view1;
    view.reset(sf::FloatRect(0,0,640,640));

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

        window.setView(view);

        window.clear(sf::Color::Blue);
        window.draw(bg);


        window.display();
    }

    return EXIT_SUCCESS;
}
