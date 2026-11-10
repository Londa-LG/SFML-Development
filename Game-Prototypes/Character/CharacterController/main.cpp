#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <tuple>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <iostream>

class cShape;
class GameEngine;
class cTransform;
class cBoundingBox;

using ComponentTuple = std::tuple<cTransform,cShape,cBoundingBox>;

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
    private:
        int id;
        bool alive;
        std::string tag;
        ComponentTuple components;

    friend class EntityManager;

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
        T& addComponents(TArgs&&... mArgs)
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

class EntityManager
{
    int totalEntities = 0;
    std::vector<std::shared_ptr<Entity>> ents;
    std::vector<std::shared_ptr<Entity>> toAdd;
    std::multimap<std::string,std::shared_ptr<Entity>> entityMap;

    public:
        void update()
        {
            for(int i=0;i<toAdd.size();i++)
            {
                ents.push_back(toAdd[i]);
                entityMap.insert(std::pair<std::string,std::shared_ptr<Entity>>(toAdd[i]->tag,toAdd[i]));
            }
            toAdd.clear();
        }

        std::shared_ptr<Entity> addEntity(std::string tag)
        {
            std::shared_ptr<Entity> ent = std::make_shared<Entity>(true,tag,totalEntities);
            toAdd.push_back(ent);
            totalEntities++;

            return ent;
        }

        std::vector<std::shared_ptr<Entity>> getEntities(std::string key)
        {
            std::vector<std::shared_ptr<Entity>> entv;
            std::multimap<std::string,std::shared_ptr<Entity>>::iterator it;
            std::pair<std::multimap<std::string,std::shared_ptr<Entity>>::iterator, std::multimap<std::string,std::shared_ptr<Entity>>::iterator> ret;

            ret = entityMap.equal_range(key);
            for(it=ret.first; it!=ret.second; ++it)
            {
                entv.push_back(it->second);
            }

            return entv;
        }

        void removeEntity()
        {
            totalEntities--;
        }
};

class Scene
{
    protected:
        bool paused = false;
        bool hasEnded = false;
        EntityManager entities = EntityManager();
        GameEngine *game;

    public:
        virtual void sDraw() = 0;
        virtual void sUpdate() = 0;
};

class Gameplay_Scene: public Scene
{
    public:
    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;
    int fps = 60;
    float deltaTime = 1.0f / fps;
    sf::RenderWindow window;
    std::shared_ptr<Entity> player;

    Gameplay_Scene()
    {

        // Create window
        window.create(sf::VideoMode(800,600),"Asteroids");
        window.setFramerateLimit(fps);

        // Create player
        player = entities.addEntity("player");

        // Add cShape
        sf::ConvexShape arrow;
        arrow.setPointCount(6);
        arrow.setPosition(400,300);
        arrow.setOutlineThickness(5);
        arrow.setFillColor(sf::Color::Blue);
        arrow.setOutlineColor(sf::Color::Blue);
        arrow.setPoint(0, sf::Vector2f(0,0));
        arrow.setPoint(1, sf::Vector2f(30,15));
        arrow.setPoint(2, sf::Vector2f(0,30));
        arrow.setPoint(3, sf::Vector2f(0,25));
        arrow.setPoint(4, sf::Vector2f(25,15));
        arrow.setPoint(5, sf::Vector2f(0,5));
        arrow.setRotation(270);
        player->addComponents<cShape>(arrow);

        // Add cTransform

        sf::Vector2f position = {400,300};
        sf::Vector2f velocity = {0,0};
        sf::Vector2f maxVelocity {400,400};
        sf::Vector2f acceleration {200,200};
        player->addComponents<cTransform>(position,velocity,maxVelocity,acceleration);
    }

    void sMovement()
    {
        cTransform trn = player->getComponent<cTransform>();
        if((movingUp == true) && (movingDown == false))
        {
            if(trn.velocity.y <= -trn.acceleration.y)
            {
                player->getComponent<cTransform>().velocity.y = -trn.maxVelocity.y;
                player->getComponent<cTransform>().position.y += trn.velocity.y * deltaTime;
            }
            else{
                player->getComponent<cTransform>().velocity.y -= trn.acceleration.y;
                player->getComponent<cTransform>().position.y += trn.velocity.y * deltaTime;
            }
        }
        if((movingDown == true) && (movingUp == false))
        {
            if(trn.velocity.y >= trn.acceleration.y)
            {
                player->getComponent<cTransform>().velocity.y = trn.maxVelocity.y;
                player->getComponent<cTransform>().position.y += trn.velocity.y * deltaTime;
            }
            else{
                player->getComponent<cTransform>().velocity.y += trn.acceleration.y;
                player->getComponent<cTransform>().position.y += trn.velocity.y * deltaTime;
            }
        }
        if((movingLeft == true) && (movingRight == false))
        {
            if(trn.velocity.x <= -trn.acceleration.x)
            {
                player->getComponent<cTransform>().velocity.x = -trn.maxVelocity.x;
                player->getComponent<cTransform>().position.x += trn.velocity.x * deltaTime;
            }
            else{
                player->getComponent<cTransform>().velocity.x -= trn.acceleration.x;
                player->getComponent<cTransform>().position.x += trn.velocity.x * deltaTime;
            }
        }
        if((movingRight == true) && (movingLeft == false))
        {
            if(trn.velocity.x >= trn.acceleration.x)
            {
                player->getComponent<cTransform>().velocity.x = trn.maxVelocity.x;
                player->getComponent<cTransform>().position.x += trn.velocity.x * deltaTime;
            }
            else{
                player->getComponent<cTransform>().velocity.x += trn.acceleration.x;
                player->getComponent<cTransform>().position.x += trn.velocity.x * deltaTime;
            }
        }

        if((movingRight == false) && (movingLeft == false) && (movingUp == false) && (movingDown == false))
        {
            player->getComponent<cTransform>().velocity.x = 0;
            player->getComponent<cTransform>().velocity.y = 0;
        }

        player->getComponent<cShape>().shape.setPosition(trn.position.x,trn.position.y);
    }

        void sUpdate() override
        {
            sMovement();
            sDraw();
        }

        void sDraw() override
        {
            window.clear(sf::Color::White);
            window.draw(player->getComponent<cShape>().shape);
            window.display();
        }
};


int main()
{
    Gameplay_Scene scene = Gameplay_Scene();

    while (scene.window.isOpen())
    {
        sf::Event event;
        while(scene.window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                scene.window.close();
            }
            if(event.type == sf::Event::MouseMoved)
            {
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if((event.key.code == sf::Keyboard::A)||(event.key.code == sf::Keyboard::Left))
                {
                    scene.movingLeft = true;
                }
                if((event.key.code == sf::Keyboard::D)||(event.key.code == sf::Keyboard::Right))
                {
                    scene.movingRight = true;
                }
                if((event.key.code == sf::Keyboard::S)||(event.key.code == sf::Keyboard::Down))
                {
                    scene.movingDown = true;
                }
                if((event.key.code == sf::Keyboard::W)||(event.key.code == sf::Keyboard::Up))
                {
                    scene.movingUp = true;
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if((event.key.code == sf::Keyboard::A)||(event.key.code == sf::Keyboard::Left))
                {
                    scene.movingLeft = false;
                }
                if((event.key.code == sf::Keyboard::D)||(event.key.code == sf::Keyboard::Right))
                {
                    scene.movingRight = false;
                }
                if((event.key.code == sf::Keyboard::W)||(event.key.code == sf::Keyboard::Up))
                {
                    scene.movingUp = false;
                }
                if((event.key.code == sf::Keyboard::S)||(event.key.code == sf::Keyboard::Down))
                {
                    scene.movingDown = false;
                }
            }
        }

        scene.sUpdate();
    }
    return 0;
}
