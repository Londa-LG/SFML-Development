#include <SFML/Graphics.hpp>
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Shapes");

    // Shapes

    // Circle
    sf::CircleShape circle;
    circle.setRadius(20);
    circle.setPosition(10, 20);
    circle.setOutlineThickness(5);
    circle.setFillColor(sf::Color::Red);
    circle.setOutlineColor(sf::Color::Red);

    //Rectangle
    sf::RectangleShape rectangle;
    rectangle.setPosition(30,80);
    rectangle.setRotation(45);
    rectangle.setOutlineThickness(5);
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setSize(sf::Vector2f(25,25));
    rectangle.setOutlineColor(sf::Color::Red);

    //Triangle
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPosition(10,140);
    triangle.setOutlineThickness(5);
    triangle.setFillColor(sf::Color::Red);
    triangle.setPoint(0, sf::Vector2f(0,0));
    triangle.setPoint(1, sf::Vector2f(0,10));
    triangle.setPoint(2, sf::Vector2f(25,5));
    triangle.setOutlineColor(sf::Color::Red);

    //Octagon
    sf::ConvexShape octagon;
    octagon.setPointCount(8);
    octagon.setPosition(20,160);
    octagon.setOutlineThickness(5);
    octagon.setFillColor(sf::Color::Red);
    octagon.setOutlineColor(sf::Color::Red);
    octagon.setPoint(0, sf::Vector2f(0,0));
    octagon.setPoint(1, sf::Vector2f(20,0));
    octagon.setPoint(2, sf::Vector2f(30,10));
    octagon.setPoint(3, sf::Vector2f(30,30));
    octagon.setPoint(4, sf::Vector2f(20,40));
    octagon.setPoint(5, sf::Vector2f(0,40));
    octagon.setPoint(6, sf::Vector2f(-10,30));
    octagon.setPoint(7, sf::Vector2f(-10,10));

    //Arrow
    sf::ConvexShape arrow;
    arrow.setPointCount(6);
    arrow.setPosition(20,220);
    arrow.setOutlineThickness(5);
    arrow.setFillColor(sf::Color::Blue);
    arrow.setOutlineColor(sf::Color::Blue);
    arrow.setPoint(0, sf::Vector2f(0,0));
    arrow.setPoint(1, sf::Vector2f(30,15));
    arrow.setPoint(2, sf::Vector2f(0,30));
    arrow.setPoint(3, sf::Vector2f(0,25));
    arrow.setPoint(4, sf::Vector2f(25,15));
    arrow.setPoint(5, sf::Vector2f(0,5));

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

        window.clear();

        // draw shapes
        window.draw(arrow);
        window.draw(circle);
        window.draw(octagon);
        window.draw(triangle);
        window.draw(rectangle);

        // display
        window.display();
    }

    return EXIT_SUCCESS;
}
