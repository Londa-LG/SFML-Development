#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>

sf::Vector2f normalize(sf::Vector2f vect)
{
    sf::Vector2f normalized;
    float hyp = sqrt(pow(vect.x,2) + pow(vect.y,2));
    normalized = sf::Vector2f((vect.x/hyp),(vect.y/hyp));

    return normalized;
}

sf::Sprite sMovement(bool up,bool down,bool left,bool right,sf::Sprite sprite,std::shared_ptr<sf::Vector2f> position)
{
    // Set up
    float deltaTime = 1.0f/60;
    sf::Vector2f speed = {200,200};
    sf::Vector2f normalized = normalize(speed);

    // Movement
    if((up == true) && (down == false) && (left == false) && (right == false))
    {
        position->y -= speed.y * deltaTime;
        sprite.setPosition(*position);
    }
    if((down == true) && (up == false) && (left == false) && (right == false))
    {
        position->y += speed.y * deltaTime;
        sprite.setPosition(*position);
    }
    if((left == true) && (up == false) && (down == false) && (right == false))
    {
        position->x -= speed.x * deltaTime;
        sprite.setPosition(*position);
    }
    if((right == true) && (up == false) && (left == false) && (down == false))
    {
        position->x += speed.x * deltaTime;
        sprite.setPosition(*position);
    }

    return sprite;
}
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Topdown character");
    window.setFramerateLimit(60);

    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position = {400,300};
    texture.loadFromFile("Warrior_Run.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,192,192));
    sprite.setColor(sf::Color::White);
    sprite.setPosition(position);
    std::shared_ptr<sf::Vector2f> positionPtr = std::make_shared<sf::Vector2f>(position);



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
                if(event.key.code == sf::Keyboard::Up)
                {
                    movingUp = true;
                }
                if(event.key.code == sf::Keyboard::Down)
                {
                    movingDown = true;
                }
                if(event.key.code == sf::Keyboard::Left)
                {
                    movingLeft = true;
                }
                if(event.key.code == sf::Keyboard::Right)
                {
                    movingRight = true;
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Up)
                {
                    movingUp = false;
                }
                if(event.key.code == sf::Keyboard::Down)
                {
                    movingDown = false;
                }
                if(event.key.code == sf::Keyboard::Left)
                {
                    movingLeft = false;
                }
                if(event.key.code == sf::Keyboard::Right)
                {
                    movingRight = false;
                }
            }
        }

        sprite = sMovement(movingUp,movingDown,movingLeft,movingRight,sprite,positionPtr);

        window.clear(sf::Color::Yellow);
        window.draw(sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}
