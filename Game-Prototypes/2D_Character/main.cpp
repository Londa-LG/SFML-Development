#include <SFML/Graphics.hpp>
#include <memory>

sf::RectangleShape getOutlineRect(float x,float y,float width,float height)
{
    sf::RectangleShape rect;

    rect.setPosition(x,y);
    rect.setOutlineThickness(2);
    rect.setSize(sf::Vector2f(width,height));
    rect.setOutlineColor(sf::Color::Blue);
    
    return rect;
}

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
    sf::Vector2f size;
    sf::Vector2f position;
    float top = position.y;
    float left = position.x;
    float right = position.x + size.x;
    float bottom = position.y + size.y;

    sf::RectangleShape outline;
};

struct Transform
{
    float mass;
    float acceleration;
};

class Character
{
    public:
    float deltaTime = 1/60;

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
    Transform transform;

    Character(){}

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
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width /2.f, bounds.height /2.f);
        sprite.setScale(-1.f,1.f);
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

        window.clear(sf::Color::White);
        window.display();
    }

    return EXIT_SUCCESS;
}
