#include <SFML/Graphics.hpp>
#include "Inventory.h"

sf::Sprite generate_sprite(sf::Texture& texture,sf::IntRect rect)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    
    return sprite;
}

sf::IntRect generate_rect_weapon(int col)
{
    int row = 5;
    sf::IntRect rect = sf::IntRect((col*32),(row*32),32,32);
    return rect;
}

Weapon generate_weapon(sf::Texture& texture,int id,int required_strength,int damage,int durability)
{
    sf::IntRect wr = generate_rect_weapon(2);
    sf::Sprite sprite = generate_sprite(texture,wr);
    sprite.setPosition(300,300);

    return Weapon(id,ItemType::weapon,sprite,required_strength,damage,durability);
}
/*
sf::Sprite generate_sprite_consumable()
{
}

sf::Sprite generate_sprite_money()
{
}

sf::Sprite generate_sprite_quest_item()
{
}
*/
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("icons/Black_BG.png");
    Item w1 = generate_weapon(texture,1,5,10,30);

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

        window.clear(sf::Color::Yellow);
        window.draw(w1.sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}
