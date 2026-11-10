#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Character
{
    public:
    float speed;
    bool jumping;
    float gravForce;
    float deltaTime;
    float jumpHeight;
    float destination;
    sf::RectangleShape rect;

    Character()
    {
        jumping = false;
        speed = 400;
        gravForce = 120;
        jumpHeight = 100;
        deltaTime = 1.0f/60;
        rect.setPosition(380,280);
        rect.setOutlineThickness(2);
        rect.setSize(sf::Vector2f(40,40));
        rect.setFillColor(sf::Color::White);
        rect.setOutlineColor(sf::Color::White);
    }

    void update()
    {
        if(jumping)
        {
            sf::Vector2f pos = rect.getPosition(); 
            if(pos.y > destination)
            {
                float normalized = normalize(pos.y,destination);
                pos.y += normalized * speed * deltaTime;
                rect.setPosition(pos);
            }
            else
            {
                jumping = false;
            }
        }
        else
        {
            gravity();
        }
    }
    float normalize(float pos,float dest)
    {
        float dy = dest - pos;
        float hyp = sqrt(pow(dy,2));
        float normalized = dy/hyp;
        
        return normalized;
    }
    void jump()
    {
        sf::Vector2f pos = rect.getPosition(); 
        destination = pos.y - jumpHeight;
        jumping = true;
    }
    void gravity()
    {
        sf::Vector2f pos = rect.getPosition(); 
        if(pos.y < 340)
        {
            pos.y += gravForce * deltaTime;
            rect.setPosition(pos);
        }
    }
};
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

    Character player = Character();

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
                if(event.key.code == sf::Keyboard::Space)
                {
                    player.jump();
                }
            }


        }
        
        player.update();

        window.clear(sf::Color::Yellow);
        window.draw(player.rect);
        window.display();
    }

    return EXIT_SUCCESS;
}
