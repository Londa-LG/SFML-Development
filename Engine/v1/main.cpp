#include <SFML/Graphics.hpp>
#include <tuple>
#include <memory>
#include <vector>
#include <map>
#include <string>

struct Rectangle
{
    float x;
    float y;
    float width;
    float height;
};

class Component
{
    public:
        bool exists = false;
};

class cTransform: public Component
{
    public:
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f maxVelocity;
        sf::Vector2f acceleration;

    cTransform(){}

    cTransform(sf::Vector2f pPosition,sf::Vector2f pVelocity,sf::Vector2f pAcceleration,sf::Vector2f pMaxVelocity)
    {
        position = pPosition;
        velocity = pVelocity;
        maxVelocity = pMaxVelocity;
        acceleration = pAcceleration;
    }
};

class cShape: public Component
{
    public:
        sf::ConvexShape shape;

    cShape(){}

    cShape(sf::ConvexShape pShape)
    {
        shape = pShape;
    }
};

class cBoundingBox: public Component
{
    public:
        Rectangle rect;

    cBoundingBox(){}

    cBoundingBox(Rectangle pRect)
    {
        rect = pRect;
    }
};

class Entity
{
};

int main()
{
    return 0;
}



































































































