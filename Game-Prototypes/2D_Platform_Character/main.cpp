#include <SFML/Graphics.hpp>
#include <memory>
#include <math.h>
#include <iostream>


struct Animation
{
    int index = 0;
    std::string name;
    sf::Vector2i frameSize;
    std::vector<sf::Vector2i> frames;
    std::shared_ptr<sf::Texture> texture;
};

struct BoundingBox
{
    float top;
    float left;
    float right;
    float bottom;
    sf::Vector2i size;
    sf::Vector2f position;

    sf::RectangleShape outline;
};

struct CharacterTransform
{
    float maxVel;
    float acceleration;
    sf::Vector2f position;
};

class Character
{
    public:
    float deltaTime = 1/60;
    float moveDistance = 2; // in pixels
    float jumpVelocity = 10;

    bool fall = false;
    bool jump = false;
    bool ground = false;

    bool idle = true;
    bool running = false;
    bool walking = false;
    char direction = 'L'; // L: left or R: right

    sf::Sprite sprite;
    std::shared_ptr<Animation> currentAnimation;
    std::vector<std::shared_ptr<Animation>> animations;

    BoundingBox boundingBox;
    CharacterTransform transform;

    Character(){}

    Character(sf::Vector2i size, sf::Vector2f position,std::shared_ptr<Animation> cAnimation, std::vector<std::shared_ptr<Animation>> pAnimations)
    {
        // Init bounding Box
        boundingBox.size = size;
        boundingBox.position = position;
        boundingBox.outline = getOutlineRect(position.x,position.y,size.x,size.y);

        boundingBox.top = position.y;
        boundingBox.left = position.x;
        boundingBox.right = position.x + size.x;
        boundingBox.bottom = position.y + size.y;

        // Init Animations
        animations  = pAnimations;
        currentAnimation = cAnimation;
        sprite.setTexture(*currentAnimation->texture);
        sprite.setPosition(boundingBox.left,boundingBox.top);
        int i = currentAnimation->index;
        sprite.setTextureRect(sf::IntRect(currentAnimation->frames[i].x,currentAnimation->frames[i].y,currentAnimation->frameSize.x,currentAnimation->frameSize.y));

        // Init Transform
        calAcceleration(moveDistance);
        transform.maxVel = 10;
        transform.position = position;
    }

    sf::RectangleShape getOutlineRect(float x,float y,float width,float height)
    {
        sf::RectangleShape rect;

        rect.setPosition(x,y);
        rect.setOutlineThickness(2);
        rect.setSize(sf::Vector2f(width,height));
        rect.setOutlineColor(sf::Color::Blue);
        rect.setFillColor(sf::Color::Transparent);
    
        return rect;
    }

    void calAcceleration(float pix)
    {
        transform.maxVel =  pix / (0.5 * 1);
        transform.acceleration = pow(transform.maxVel,2) / (2*pix);
    }

    void changeAnimation(std::string name)
    {
        for(int i=0; i<animations.size();i++)
        {
            if(animations[i]->name == name)
            {
                currentAnimation = animations[i];
            }
        }
    }

    void flipSprite()
    {
        sprite.setTextureRect(sf::IntRect(boundingBox.size.x,0,-boundingBox.size.x,boundingBox.size.y));
    }

    void sAnimate()
    {
        if(currentAnimation->index < (currentAnimation->frames.size() -1))
        {
            currentAnimation->index += currentAnimation->frames.size() * deltaTime;
        }
        else
        {
            currentAnimation->index = 0;
        }

        int i = currentAnimation->index;
        sprite.setTextureRect(sf::IntRect(currentAnimation->frames[i].x,currentAnimation->frames[i].y,currentAnimation->frameSize.x,currentAnimation->frameSize.y));
    }

    void sMovement()
    {
        if(running)
        {
            if(direction == 'L')
            {
                transform.position.x -= transform.acceleration;
                boundingBox.position = transform.position;
                boundingBox.outline.setPosition(transform.position);
                sprite.setPosition(boundingBox.position);

            }
            else if(direction == 'R')
            {
                transform.position.x += transform.acceleration;
                boundingBox.position = transform.position;
                boundingBox.outline.setPosition(transform.position);
                sprite.setPosition(boundingBox.position);
            }
        }
        if(jump)
        {
        }
    }

    void sGravity()
    {
    }

    void update()
    {
        sMovement();
        sGravity();
        sAnimate();
    }

    void display(sf::RenderWindow& window)
    {
        if(direction == 'L')
        {
            flipSprite();
        }

        window.draw(sprite);
    }
};
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

    sf::Vector2f position = {400,300};
    std::vector<sf::Vector2i> frames;
    sf::Vector2i frameSize = sf::Vector2i(32,32);

    sf::Texture runAnimation;
    sf::Texture idleAnimation;
    runAnimation.loadFromFile("./Pink_Man/Run (32x32).png");
    idleAnimation.loadFromFile("./Pink_Man/Idle (32x32).png");

    std::shared_ptr<Animation> idle = std::make_shared<Animation>();
    std::shared_ptr<Animation> run = std::make_shared<Animation>();
    std::vector<std::shared_ptr<Animation>> animations;

    // Animations
    //Idle
    for(int i=0; i<11;i++)
    {
        frames.push_back(sf::Vector2i((i * frameSize.x),0));
    }
    idle->name = "idle";
    idle->frames = frames;
    idle->frameSize = frameSize;
    idle->texture = std::make_shared<sf::Texture>(idleAnimation);
    frames.clear();
    //Run
    for(int i=0;i<12;i++)
    {
        frames.push_back(sf::Vector2i((i * frameSize.x),0));
    }
    run->name = "run";
    run->frames = frames;
    run->frameSize = frameSize;
    run->texture = std::make_shared<sf::Texture>(runAnimation);

    animations.push_back(idle);
    animations.push_back(run);

    Character player = Character(frameSize,position,idle,animations);

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
                if(event.key.code == sf::Keyboard::A)
                {
                    player.direction = 'L';
                    player.running = true;
                }
                if(event.key.code == sf::Keyboard::D)
                {
                    player.direction = 'R';
                    player.running = true;
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::A)
                {
                    player.running = false;
                }
                if(event.key.code == sf::Keyboard::D)
                {
                    player.running = false;
                }
            }
        }

        player.update();

        window.clear(sf::Color::White);
        player.display(window);
        window.draw(player.boundingBox.outline);
        window.display();
    }

    return EXIT_SUCCESS;
}






























