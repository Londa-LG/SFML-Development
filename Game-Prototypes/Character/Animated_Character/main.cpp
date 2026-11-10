#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

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
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Animated Characters");
    window.setFramerateLimit(60);

    std::vector<sf::Vector2i> frames;
    sf::Vector2i size = sf::Vector2i(78,58);

    for(int i=0; i<11;i++)
    {
        frames.push_back(sf::Vector2i((i * size.x),0));
    }
    Animation idle = Animation(11,frames,size,"./assets/Idle (78x58).png");
    idle.scale(2,2);
    frames.clear();

    for(int i=0; i<8;i++)
    {
        frames.push_back(sf::Vector2i((i * size.x),0));
    }
    Animation run = Animation(8,frames,size,"./assets/Run (78x58).png");
    run.scale(2,2);
    run.setPosition(0,59);
    frames.clear();

    for(int i=0; i<3;i++)
    {
        frames.push_back(sf::Vector2i((i * size.x),0));
    }
    Animation attack = Animation(3,frames,size,"./assets/Attack (78x58).png");
    attack.scale(2,2);
    attack.setPosition(0,177);
    frames.clear();

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
        idle.animate();
        run.animate();
        attack.animate();

        window.clear(sf::Color::Yellow);
        window.draw(idle.getSprite());
        window.draw(run.getSprite());
        window.draw(attack.getSprite());
        window.display();
    }

    return EXIT_SUCCESS;
}
