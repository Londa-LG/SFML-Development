#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <tuple>
#include <memory>
#include <vector>
#include <map>
#include <string>

class GameEngine;
class cTransform;
class cBoundingBox;

using ComponentTuple = std::tuple<cTransform,cBoundingBox>;

class Action
{
    std::string name;
    std::string type;

    public:
        //std::shared_ptr<std::string> name()
        void getName()
        {
        }
        //std::shared_ptr<std::string> type()
        void getTpe()
        {
        }
};

class Animation
{
    float deltaTime = 1.0f/60;
    int frameCount;
    sf::Sprite sprite;
    float frameIndex = 0;
    sf::Texture animation;
    sf::Vector2i frameSize;
    std::vector<sf::Vector2i> frames;

    public:
        Animation(int pCount,std::vector<sf::Vector2i> pFrames,sf::Vector2i pSize,std::string pAnimation)
        {
            frames = pFrames;
            frameSize = pSize;
            frameCount = pCount;
            animation.loadFromFile(pAnimation);
            sprite.setTexture(animation);
            sprite.setTextureRect(sf::IntRect(frames[frameIndex].x,frames[frameIndex].y,frameSize.x,frameSize.y));
            sprite.setColor(sf::Color::White);
        }
        void scale(int x,int y)
        {
            sprite.scale(x,y);
        }
        void setPosition(int x,int y)
        {
            sprite.setPosition(x,y);
        }
        void animate()
        {
            if(frameIndex < (frameCount - 1))
            {
                frameIndex += frameCount * deltaTime;
                //frameIndex++;
            }
            else
            {
                frameIndex = 0;
            }
            int i = (int)frameIndex;
            sprite.setTextureRect(sf::IntRect(frames[i].x,frames[i].y,frameSize.x,frameSize.y));
        }
        sf::Sprite getSprite()
        {
            return sprite;
        }
};

class Assets
{
    std::map<std::string,sf::Font> fonts;
    std::map<std::string,sf::Sound> sounds;
    std::map<std::string,sf::Texture> textures;
    std::map<std::string,Animation> animations;

    public:
        void addTexture(std::string name,std::string path)
        {
        }
        void addAnimation(std::string name,Animation animation)
        {
        }
        void addSound(std::string name, std::string path)
        {
        }
        void addFont(std::string name, std::string path)
        {
        }

        //std::shared_ptr<sf::Texture> getTexture(std::string name)
        void getTexture()
        {
        }
        //std::shared_ptr<Animation> getAnimation(std::string name)
        void getAniamtion()
        {
        }
        //std::shared_ptr<sf::Sound> getSound(std::string name)
        void getSound()
        {
        }
        //std::shared_ptr<sf::Font> getFont(std::string name)
        void getFont()
        {
        }
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

class cBoundingBox: public Component
{
    public:
        sf::FloatRect rect;

    cBoundingBox(){}

    cBoundingBox(sf::FloatRect pRect)
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

class Physics
{
    public:
        bool isCollision(std::shared_ptr<Entity> ent1,std::shared_ptr<Entity> ent2)
        {
            return false;
        }
};


class Scene
{
    protected:
        static bool paused;
        static bool hasEnded;
        static int currentFrame;
        static EntityManager entities;
        static std::shared_ptr<GameEngine> game;
        static std::map<int,std::string> actionMap;

    public:
        virtual void update() = 0;
        virtual void sRender() = 0;
        virtual void sDoAction() = 0;
};

class Scene_Play : Scene
{
    std::string levelPath;
    std::shared_ptr<Entity> player;

    public:
        void init()
        {
        }
        void update() override
        {
        }

        // Systems
        void sAnimation()
        {
        }
        void sMovements()
        {
        }
        void sEnemySpawner()
        {
        }
        void sCollision()
        {
        }
        void sRender() override
        {
        }
        void sDoAction() override
        {
        }
        void sDebug()
        {
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
        }
        void update() override
        {
        }

        //Systems
        void sRender() override
        {
        }
        void sDoAction() 
        {
        }
};

class GameEngine
{
    bool running;
    Assets assets;
    sf::RenderWindow window;
    std::string currentScene;
    std::map<std::string,Scene> scenes;

    public:
        void init()
        {
        }
        //std::shared_ptr<Scene> getCurrentScene()
        void getCurrentScene()
        {
        }
        void run()
        {
        }
        void update()
        {
        }
        void quit()
        {
        }
        void changeScene(std::string)
        {
        }
        void getAssets()
        {
        }
        void getWindow()
        {
        }
        void sUserInput()
        {
        }
};

int main()
{
    return 0;
}

