#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

sf::CircleShape sGenerateSprite()
{
    sf::CircleShape projectile;
    projectile.setRadius(10);
    projectile.setPosition(400,300);
    projectile.setOutlineThickness(5);
    projectile.setFillColor(sf::Color::White);
    projectile.setOutlineColor(sf::Color::White);

    return projectile;
}

sf::Vector2f sNormalize(sf::Vector2f vect,sf::Vector2f destination)
{
    sf::Vector2f normalized;
    float dx = destination.x - vect.x;
    float dy = destination.y - vect.y;
    float hyp = sqrt(pow(dx,2) + pow(dy,2));
    normalized = sf::Vector2f((dx/hyp),(dy/hyp));

    return normalized;
}

sf::CircleShape sMoveProjectile(sf::Vector2i destination,sf::CircleShape projectile)
{
    int speed = 200;
    float deltaTime = 1.0f/60;
    sf::Vector2f dest = sf::Vector2f(destination.x,destination.y);
    sf::Vector2f pos = projectile.getPosition();
    sf::Vector2f normalized = sNormalize(pos,dest);
    pos.x += normalized.x * speed * deltaTime;
    pos.y += normalized.y * deltaTime * speed;

    projectile.setPosition(pos);

    return projectile;
}
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Projectile");
    window.setFramerateLimit(60);
                    
    sf::CircleShape proj;
    sf::Vector2i mPos;

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
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    mPos = sf::Mouse::getPosition(window);
                    proj = sGenerateSprite();
                }
            }
        }

        proj = sMoveProjectile(mPos,proj);

        window.clear(sf::Color::Yellow);
        window.draw(proj);
        window.display();
    }

    return EXIT_SUCCESS;
}
