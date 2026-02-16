#include <SFML/Graphics.hpp>
#include <memory>

class cTransform;
class cBoundingBox;

using ComponentTuple = std::tuple<cTransform,cBoundingBox>;

struct Collision{
    bool occured = false;
    bool xMovement = false;
    bool yMovement = false;
};

class Component
{
    public:
        bool exists = false;
};

class cTransform: public Component
{
    public:
        sf::Vector2f position; // Bounding rect center
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

class cBoundingBox: public Component
{
    public:
        sf::FloatRect rect;

    cBoundingBox(){}

    cBoundingBox(sf::FloatRect pRect)
    {
        rect = pRect;
    }

    void updatePosition(float x,float y)
    {
        rect.left = x - (rect.width/2);
        rect.top = y - (rect.height/2);
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

class Physics
{
    public:
        Collision isCollision(std::shared_ptr<Entity> ent1,std::shared_ptr<Entity> ent2)
        {
            Collision collision;

            sf::FloatRect ent1B = ent1->getComponent<cBoundingBox>().rect; 
            sf::FloatRect ent2B = ent1->getComponent<cBoundingBox>().rect;
            float deltaX = abs((ent1B.left + ent1B.width) - (ent2B.left + ent2B.width));
            float deltaY = abs((ent1B.top + ent1B.height) - (ent2B.top + ent2B.height));
            float overlapX = (ent1B.width/2) + (ent2B.width/2) - deltaX;
            float overlapY = (ent1B.height/2) + (ent2B.height/2) - deltaY;

            if((overlapX >0) || (overlapY >0))
            {
                if(overlapX > 0)
                {
                    collision.yMovement = true;
                }
                else if(overlapY > 0)
                {
                    collision.xMovement = true;
                }
            }

            return collision;
        }
};

class Scene
{
    protected:
        static bool paused;
        static bool hasEnded;
        static int currentFrame;
        static EntityManager entities;
        static std::map<int,std::string> actionMap;
        static std::shared_ptr<sf::RenderWindow> window;

    public:
        virtual void update() = 0;
        virtual void sRender() = 0;
        virtual void sDoAction() = 0;
};

class Scene_Play : Scene
{
    std::string levelPath;
    std::shared_ptr<Entity> player;
    std::shared_ptr<std::map<std::string,sf::IntRect>> map;

    public:
        void init(std::shared_ptr<std::map<std::string,sf::IntRect>> pMap)
        {
            // Edit
            map = pMap;
        }
        void update() override
        {
            // Edit
        }

        // Systems
        void sAnimation()
        {
            // Edit
        }
        void sMovements()
        {
            // Edit
        }
        void sEnemySpawner()
        {
            // Edit
        }
        void sCollision()
        {
            // Edit
        }
        void sRender() override
        {
            //Render World
            //Render Characters
        }
        void sDoAction() override
        {
            // Edit
        }
        void sDebug()
        {
            // Edit
        }
};

class Scene_Menu : Scene
{
    int menuIndex;
    sf::Text menuText;
    std::vector<std::string> levelPaths;
    std::vector<std::string> menuStrings;

    public:
        void init()
        {
            // Edit
        }
        void update() override
        {
            // Edit
        }

        //Systems
        void sRender() override
        {
            // Edit
        }
        void sDoAction() 
        {
            // Edit
        }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(600,600), "Collisions");
    window.setFramerateLimit(60);

    Scene_Play gameplay = Scene_Play();
    Scene_Menu menu = Scene_Menu();

    bool currentScene = true;

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

        window.clear(sf::Color::Red);
        if(currentScene)
        {
            gameplay.update();
        }
        else
        {
            menu.update();
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
