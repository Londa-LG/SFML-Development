#include <SFML/Graphics.hpp>
#include <cmath>

sf::ConvexShape sChaserAI(sf::CircleShape player,sf::ConvexShape chaser)
{
    float deltaTime = 1.0f/60;
    sf::Vector2f target = player.getPosition();
    sf::Vector2f position = chaser.getPosition();
    float distanceX = target.x - position.x;
    float distanceY = target.y - position.y;
    float hyp = sqrt((pow(distanceX,2) + pow(distanceY,2)));
    sf::Vector2f normalized = sf::Vector2f((distanceX/hyp),(distanceY/hyp));

    position.x = position.x + normalized.x;
    position.y = position.y + normalized.y;

    chaser.setPosition(position.x,position.y);

    return chaser;
}
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

    sf::CircleShape player;
    player.setRadius(10);
    player.setPosition(400,300);
    player.setOutlineThickness(8);
    player.setFillColor(sf::Color::Transparent);
    player.setOutlineColor(sf::Color::White);

    sf::ConvexShape chaser;
    chaser.setPointCount(6);
    chaser.setPosition(700,300);
    chaser.setOutlineThickness(8);
    chaser.setOutlineColor(sf::Color::White);
    chaser.setFillColor(sf::Color::Transparent);
    chaser.setPoint(0, sf::Vector2f(20,0));
    chaser.setPoint(1, sf::Vector2f(40,0));
    chaser.setPoint(2, sf::Vector2f(50,20));
    chaser.setPoint(3, sf::Vector2f(40,40));
    chaser.setPoint(4, sf::Vector2f(20,40));
    chaser.setPoint(5, sf::Vector2f(10,20));

    

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

        chaser = sChaserAI(player,chaser);

        window.clear(sf::Color::Yellow);
        window.draw(player);
        window.draw(chaser);
        window.display();
    }

    return EXIT_SUCCESS;
}
