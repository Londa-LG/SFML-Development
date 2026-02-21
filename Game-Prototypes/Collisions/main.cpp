#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <tuple>
#include <map>

class cShape;
class GameEngine;
class cTransform;
class cBoundingBox;

using ComponentTuple = std::tuple<cTransform,cBoundingBox,cShape>;

class Component
{
    public:
        bool exists = false;
};

class cShape: public Component
{
    public:
        sf::RectangleShape rect;

    cShape(){}

    cShape(sf::Vector2f size,sf::Vector2f position,sf::Color color)
    {
        rect.setSize(size);
        rect.setFillColor(color);
        rect.setPosition(position);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(color);
    }
    void updatePosition(sf::Vector2f position)
    {
        rect.setPosition(position);
    }
};

class cTransform: public Component
{
    public:
        sf::Vector2f velocity;
        sf::Vector2f maxVelocity;
        sf::Vector2f acceleration;
        sf::Vector2f currentPosition;
        sf::Vector2f previousPosition;

    cTransform(){}

    cTransform(sf::Vector2f pCPosition,sf::Vector2f pVelocity,sf::Vector2f pAcceleration,sf::Vector2f pMaxVelocity)
    {
        velocity = pVelocity;
        maxVelocity = pMaxVelocity;
        acceleration = pAcceleration;
        currentPosition = pCPosition;
    }

    void updatePosition(sf::Vector2f pCPosition)
    {
        previousPosition = currentPosition;
        currentPosition = pCPosition;
    }
};

class cBoundingBox: public Component
{
    public:
        float top;
        float left;
        float right;
        float bottom;
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

class Entity
{
    private:
        int id;
        bool alive;
        std::string tag;
        ComponentTuple components;

    public:
        Entity(bool pAlive,std::string pTag,int pID)
        {
            id = pID;
            tag = pTag;
            alive = pAlive;
        }

        void destroy()
        {
            alive = false;
        }
        
        template<typename T,typename... TArgs>
        T& addComponent(TArgs&&... mArgs)
        {
            auto & component = std::get<T>(components);
            component = T(std::forward<TArgs>(mArgs)...);
            component.exists = true;

            return component;
        }

        template<typename T>
        bool hasComponent()
        {
            return std::get<T>().exists;
        }

        template<typename T>
        T& getComponent()
        {
            return std::get<T>(components);
        }

        template<typename T>
        void removeComponent()
        {
            std::get<T>().exist = false;
        }
};


class Physics
{
    public:
        Physics(){};

        bool collisionDetection(std::shared_ptr<Entity> ent1,std::shared_ptr<Entity> ent2)
        {
            cBoundingBox b1 = ent1->getComponent<cBoundingBox>();
            cBoundingBox b2 = ent2->getComponent<cBoundingBox>();

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

        void collisionHandling(std::shared_ptr<Entity> ent1,std::shared_ptr<Entity> ent2)
        {
        }
};

void sMovement(std::shared_ptr<Entity> ent1,sf::Vector2f vel)
{
    sf::Vector2f accel = ent1->getComponent<cTransform>().currentPosition + vel;
    ent1->getComponent<cTransform>().updatePosition(accel);
    sf::Vector2f pos = ent1->getComponent<cTransform>().currentPosition;
    ent1->getComponent<cBoundingBox>().updatePosition(pos);
    ent1->getComponent<cShape>().updatePosition(pos);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),"Collisions");
    window.setFramerateLimit(60);

    // Transform
    sf::Vector2f velocity,maxVelocity;
    sf::Vector2f position1,position2,position3,position4;
    sf::Vector2f acceleration1,acceleration2,acceleration3,acceleration4;
    position1 = sf::Vector2f(0,0);
    position2 = sf::Vector2f(750,0);
    position3 = sf::Vector2f(400,0);
    position4 = sf::Vector2f(400,550);
    velocity = sf::Vector2f(0,0);
    maxVelocity = sf::Vector2f(0,0);
    acceleration1 = sf::Vector2f(1.5,0);
    acceleration2 = sf::Vector2f(-1.5,0);
    acceleration3 = sf::Vector2f(0,1.5);
    acceleration4 = sf::Vector2f(0,-1.5);

    // Shape
    sf::Vector2f size = sf::Vector2f(50,50);
    sf::Color color3 = sf::Color::Red;
    sf::Color color1 = sf::Color::Black;
    sf::Color color2 = sf::Color::White;
    sf::Color color4 = sf::Color::Green;

    // Entities
    std::shared_ptr<Entity> ent3 = std::make_shared<Entity>(true,"vertical1",2);
    std::shared_ptr<Entity> ent4 = std::make_shared<Entity>(true,"vertical2",3);
    std::shared_ptr<Entity> ent1 = std::make_shared<Entity>(true,"horizontal1",0);
    std::shared_ptr<Entity> ent2 = std::make_shared<Entity>(true,"horizontal2",1);

    //phy.collisionHandling(ent1,ent2);

    ent1->addComponent<cShape>(size,position1,color1);
    ent2->addComponent<cShape>(size,position2,color2);
    ent3->addComponent<cShape>(size,position3,color3);
    ent4->addComponent<cShape>(size,position4,color4);
    ent1->addComponent<cBoundingBox>(sf::FloatRect(position1,size));
    ent2->addComponent<cBoundingBox>(sf::FloatRect(position2,size));
    ent3->addComponent<cBoundingBox>(sf::FloatRect(position3,size));
    ent4->addComponent<cBoundingBox>(sf::FloatRect(position4,size));
    ent1->addComponent<cTransform>(position1,velocity,acceleration1,maxVelocity);
    ent2->addComponent<cTransform>(position2,velocity,acceleration1,maxVelocity);
    ent3->addComponent<cTransform>(position3,velocity,acceleration2,maxVelocity);
    ent4->addComponent<cTransform>(position4,velocity,acceleration2,maxVelocity);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Update
        sMovement(ent1,acceleration1);
        sMovement(ent2,acceleration2);
        sMovement(ent3,acceleration3);
        sMovement(ent4,acceleration4);

        // Physics
        Physics phy = Physics();
        if(phy.collisionDetection(ent1,ent2))
        {
            std::cout << "Horizontal collision: Yes" << std::endl;
        }
        else
        {
            std::cout << "Horizontal collision: No" << std::endl;
        }
/*
        if(phy.collisionDetection(ent3,ent4))
        {
            std::cout << "Vertical collision: Yes" << std::endl;
        }
        else
        {
            std::cout << "Vertical collision: No" << std::endl;
        }
*/
        // Render
        window.clear(sf::Color::Yellow);
        window.draw(ent1->getComponent<cShape>().rect);
        window.draw(ent2->getComponent<cShape>().rect);
        //window.draw(ent3->getComponent<cShape>().rect);
        //window.draw(ent4->getComponent<cShape>().rect);
        window.display();
    }

    return EXIT_SUCCESS;
}

