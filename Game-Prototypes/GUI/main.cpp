#include <SFML/Graphics.hpp>

struct Button{
  int id;
  sf::Text label;
  sf::Vector2f position;
  sf::RectangleShape shape;
  void(*onClick)();
};


void draw_btn(sf::RenderWindow &window,sf::Vector2f pPosition,int pl,int pt)
{
  sf::Font font;
  font.loadFromFile("m5x7.ttf");

  sf::Text label("Button", font);
  label.setCharacterSize(30);
  label.setFillColor(sf::Color::Blue);
  label.setPosition(pPosition.x + pl,pPosition.y + pt);

  sf::RectangleShape rectangle;
  rectangle.setPosition(pPosition);
  rectangle.setOutlineThickness(2);
  rectangle.setFillColor(sf::Color::Yellow);
  rectangle.setSize(sf::Vector2f(100,50));
  rectangle.setOutlineColor(sf::Color::Blue);

  window.draw(rectangle);
  window.draw(label);
}

 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "GUI");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("m5x7.ttf");

    sf::Text button("Button", font);
    button.setCharacterSize(30);
    button.setFillColor(sf::Color::Blue);
    button.setPosition(100,100);

    sf::RectangleShape rectangle;
    rectangle.setPosition(90,95);
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setSize(sf::Vector2f(100,50));
    rectangle.setOutlineColor(sf::Color::Blue);

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
        draw_btn(window,{300,200},10,10);
        window.display();
    }

    return EXIT_SUCCESS;
}
