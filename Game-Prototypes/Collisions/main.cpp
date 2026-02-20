#include <SFML/Graphics.hpp>
#include <iostream>

class cBoundingBox
{
    public:
        float top;
        float left;
        float right;
        float bottom;
        sf::Vector2f center;
        sf::FloatRect rect;

        cBoundingBox(){}

        cBoundingBox(sf::FloatRect pRect)
        {
            updateBox(pRect);
        }

        void updateBox(sf::FloatRect pRect)
        {
            rect = pRect;
            top = rect.top;
            left = rect.left;
            right = rect.left + rect.width;
            bottom = rect.top + rect.height;

            center.x = right/2;
            center.y = bottom/2;
        }
        void updatePosition(sf::Vector2f pos)
        {
            top = pos.y;
            left = pos.x;
            right = pos.x + rect.width;
            bottom = pos.y + rect.height;
        }
        sf::Vector2f getPosition()
        {
            return sf::Vector2f(left,top);
        }

};

bool CollistionDetection(cBoundingBox b1,cBoundingBox b2)
{
    if(b1.right < b2.left)
    {
        return false;
    }
    if(b1.left > b2.right)
    {
        return false;
    }
    if(b1.bottom < b2.top)
    {
        return false;
    }
    if(b1.top > b2.bottom)
    {
        return false;
    }

    return true;
}

struct Entity
{
    cBoundingBox bBox;
    sf::RectangleShape rect;
};

void CollistionHandling(Entity& light,Entity heavy)
{
    // Horizontal
    if(light.bBox.left < heavy.bBox.right)
    {
        light.bBox.left = heavy.bBox.right;
        light.rect.setPosition(light.bBox.getPosition());
    }
    if(light.bBox.right > heavy.bBox.left)
    {
        light.bBox.right = heavy.bBox.left;
        light.rect.setPosition(light.bBox.getPosition());
    }
    // vertical
    if(light.bBox.top < heavy.bBox.bottom)
    {
        light.bBox.top = heavy.bBox.bottom;
        light.rect.setPosition(light.bBox.getPosition());
    }
    if(light.bBox.bottom > heavy.bBox.top)
    {
        light.bBox.bottom = heavy.bBox.top;
        light.rect.setPosition(light.bBox.getPosition());
    }
}

 

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

    sf::FloatRect r1 = sf::FloatRect(0,0,50,50);

    sf::Vector2f pos1,pos2,size;
    pos1.x = 0;
    pos1.y = 0;

    pos2.y = 0;;
    pos2.x = 750;

    Entity e1,e2;

    e1.rect.setPosition(pos1);
    e1.rect.setSize(sf::Vector2f(50,50));
    e1.rect.setFillColor(sf::Color::Blue);
    e1.bBox.updateBox(r1);

    e2.rect.setPosition(pos2);
    e2.rect.setSize(sf::Vector2f(50,50));
    e2.rect.setFillColor(sf::Color::White);
    e2.bBox.updateBox(r1);

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
        
        pos1.x += 0.5;
        pos2.x -= 0.5;
        e1.rect.setPosition(pos1);
        e1.bBox.updatePosition(pos1);
        e2.rect.setPosition(pos2);
        e2.bBox.updatePosition(pos2);

        if(CollistionDetection(e1.bBox,e2.bBox))
        {
            CollistionHandling(e1,e2);
            std::cout << "Collision" << std::endl;
        }
        else{
            std::cout << "No Collision" << std::endl;
        }

        window.clear(sf::Color::Yellow);
        window.draw(e1.rect);
        window.draw(e2.rect);
        window.display();
    }

    return EXIT_SUCCESS;
}
