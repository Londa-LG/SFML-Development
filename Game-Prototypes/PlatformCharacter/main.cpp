#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class Animation
{
    bool flip = false;
    float deltaTime = 1.0f/60;
    int frameCount;
    sf::Sprite sprite;
    float frameIndex = 0;
    sf::Texture animation;
    sf::Vector2i frameSize;
    std::vector<sf::Vector2i> frames;

    public:
        Animation(){}

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
        void setPosition(sf::Vector2f pos)
        {
            sprite.setPosition(pos);
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

class cBoundingBox
{
    public:
        float top;
        float left;
        float right;
        float bottom;

        float width;
        float height;

        sf::Vector2f currentPosition = sf::Vector2f(0,0);
        sf::Vector2f previousPosition = sf::Vector2f(0,0);

    cBoundingBox(){}

    cBoundingBox(float x,float y,float pWidth,float pHeight)
    {
        top = y;
        left = x;
        width = pWidth;
        height = pHeight;
        right = x + width;
        bottom = y + height;
        currentPosition = sf::Vector2f(x,y);
        previousPosition = sf::Vector2f(x,y);
    }
    void updateBox(float x,float y,float pWidth,float pHeight)
    {
        top = y;
        left = x;
        width = pWidth;
        height = pHeight;
        right = x + width;
        bottom = y + height;
        currentPosition = sf::Vector2f(x,y);
        previousPosition = sf::Vector2f(x,y);
    }
    void updatePosition(sf::Vector2f pos)
    {
        top = pos.y;
        left = pos.x;
        right = pos.x + width;
        bottom = pos.y + height;

        previousPosition = currentPosition;
        currentPosition = pos;
    }
};

struct Movement{
    bool jump = false;
    bool fall = false;
    bool left = false;
    bool right = false;
    float speed = 0;
};

struct Entity
{
    cBoundingBox rect;
    Movement movement;
    Animation currentAnimation;
    std::map<std::string,Animation> animations;
};

void sChangeAnimation(std::shared_ptr<Entity> ent,std::string changeTo)
{
    ent->currentAnimation = ent->animations[changeTo];
    ent->currentAnimation.setPosition(ent->rect.currentPosition);
}

bool collisionDetection(std::shared_ptr<Entity> ent1,std::shared_ptr<Entity> ent2)
{
    cBoundingBox b1 = ent1->rect;
    cBoundingBox b2 = ent2->rect;

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
    cBoundingBox b1 = ent1->rect;
    cBoundingBox b2 = ent2->rect;
    sf::Vector2f previousPosition1 = b1.previousPosition;

    // Handling horizontal collisions
    if((b1.right >= b2.left) && (previousPosition1.x < b1.left))
    {
        float x = b2.left - b1.width - (b1.right - b2.left);
        sf::Vector2f pos = sf::Vector2f(x,b1.top);
        ent1->rect.updatePosition(pos);
    }
    
    // Handling vertical collisions
    if((b1.bottom >= b2.top) && (previousPosition1.y < b1.top))
    {
        float y = b2.top = b1.height - (b1.bottom - b2.top);
        sf::Vector2f pos = sf::Vector2f(b1.left,y);
        ent1->rect.updatePosition(pos);
    }
}

void sGravity(std::shared_ptr<Entity> ent,float delta)
{
    float gravity = 60;
    sf::Vector2f pos = ent->rect.currentPosition;
    pos.y += gravity * delta;
    ent->rect.updatePosition(pos);
    ent->currentAnimation.setPosition(ent->rect.currentPosition);
};

void sMovement(std::shared_ptr<Entity> ent,float delta)
{
    sf::Vector2f pos = ent->rect.currentPosition;

    if(ent->movement.left)
    {
        pos.x -= ent->movement.speed * delta;
        ent->rect.updatePosition(pos);
        ent->currentAnimation.setPosition(ent->rect.currentPosition);
    }
    if(ent->movement.right)
    {
        pos.x += ent->movement.speed * delta;
        ent->rect.updatePosition(pos);
        ent->currentAnimation.setPosition(ent->rect.currentPosition);
    }
}
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Platformer character");
    window.setFramerateLimit(60);

    // Character
    std::vector<sf::Vector2i> frames;
    sf::Vector2i size = sf::Vector2i(32,32);
    std::shared_ptr<Entity> player = std::make_shared<Entity>();
    player->movement.speed = 100;
    float deltaTime = 1.0f/60;

    // Create Animations

    // Idle
    for(int i=0; i<11;i++)
    {
        frames.push_back(sf::Vector2i((i * size.x),0));
    }
    Animation idle = Animation(11,frames,size,"./Pink_Man/Idle (32x32).png");
    frames.clear();
    for(int i=0; i<11;i++)
    {
        frames.push_back(sf::Vector2i((i * size.x),0));
    }
    Animation idleLeft = Animation(11,frames,size,"./Pink_Man/IdleLeft (32x32).png");
    frames.clear();

   
    // Run
    for(int i=0;i<12;i++)
    {
        frames.push_back(sf::Vector2i((i * size.x),0));
    }
    Animation runRight = Animation(12,frames,size,"./Pink_Man/Run (32x32).png");
    frames.clear();

    for(int i=0;i<12;i++)
    {
        frames.push_back(sf::Vector2i((i * size.x),0));
    }
    Animation runLeft = Animation(12,frames,size,"./Pink_Man/RunLeft (32x32).png");
    frames.clear();

    // Jump
    frames.push_back(sf::Vector2i((0 * size.x),0));
    Animation jump = Animation(1,frames,size,"./Pink_Man/Jump (32x32).png");
    frames.clear();
    
    // Fall
    frames.push_back(sf::Vector2i((0 * size.x),0));
    Animation fall = Animation(1,frames,size,"./Pink_Man/Fall (32x32).png");
    frames.clear();

    // Add animations
    player->animations["idle"] = idle;
    player->animations["idleLeft"] = idleLeft;
    player->animations["jump"] = jump;
    player->animations["fall"] = fall;
    player->animations["runRight"] = runRight;
    player->animations["runLeft"] = runLeft;
    player->currentAnimation = player->animations["idle"];


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
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::Left))
                {
                    if(!player->movement.left)
                    {
                        player->movement.left = true;
                        sChangeAnimation(player,"runLeft");
                    }
                }
                if((event.key.code == sf::Keyboard::D) || (event.key.code == sf::Keyboard::Right))
                {
                    if(!player->movement.right)
                    {
                        player->movement.right = true;
                        sChangeAnimation(player,"runRight");
                    }
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::Left))
                {
                    if(player->movement.left)
                    {
                        player->movement.left = false;
                        sChangeAnimation(player,"idleLeft");
                    }
                }
                if((event.key.code == sf::Keyboard::D) || (event.key.code == sf::Keyboard::Right))
                {
                    if(player->movement.right)
                    {
                        player->movement.right = false;
                        sChangeAnimation(player,"idle");
                    }
                }
            }
        }


        // Update
        // Animate player
        player->currentAnimation.animate();
        // move player
        sMovement(player,deltaTime);
        // apply gravity
        sGravity(player,deltaTime);
        // handle collisions

        // Display
        window.clear(sf::Color::Yellow);
        window.draw(player->currentAnimation.getSprite());
        window.display();
    }

    return EXIT_SUCCESS;
}


















































