#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <vector>
#include <iostream>

struct ConversationBox{
  sf::Font font;
  sf::Text message;
  std::vector<sf::Text> options;
  std::vector<sf::FloatRect> bounds;

  bool clicked[4];
  sf::Vector2f size;
  sf::Vector2f position;
  sf::RectangleShape background;
};

struct Conversation{
  bool keep;
  std::string starter;
  std::vector<std::string> options;
  std::vector<std::string> responses;
};

ConversationBox get_convo_box(sf::Font &font)
{
  ConversationBox c_box;
  int text_margin_y = 25;
  int text_margin_x = 30;

  c_box.clicked[0] = false;
  c_box.clicked[1] = false;
  c_box.clicked[2] = false;
  c_box.clicked[3] = false;
  c_box.message.setFont(font);
  
  for(int i=0;i<4;i++)
  {
    c_box.options.push_back(sf::Text());
    c_box.options[i].setFont(font);
  }

  for(int i=0;i<4;i++)
  {
    c_box.bounds.push_back(sf::FloatRect());
  }

  c_box.size = {700,250};
  c_box.position = {50,290};
  c_box.background.setSize(c_box.size);
  c_box.background.setPosition(c_box.position);
  c_box.background.setOutlineColor(sf::Color::Yellow);
  c_box.background.setOutlineThickness(1);
  c_box.background.setFillColor(sf::Color::Yellow);

  c_box.message.setCharacterSize(18);
  c_box.message.setFillColor(sf::Color::Black);
  c_box.message.setPosition(c_box.position.x + text_margin_x,c_box.position.y + text_margin_y);
  c_box.message.setString("Hey,you look like someone who can handle a little trouble.Strange things have\nbeen happening nearby,the villagers are getting worried. Could you loook into it\nand come back when you know what's going on? I'll make it worth you while.");
  
  c_box.options.at(0).setCharacterSize(16);
  c_box.options[0].setFillColor(sf::Color::Black);
  c_box.options[0].setString("1. Worth my while you say.");
  c_box.options[0].setPosition(c_box.position.x + text_margin_x,c_box.position.y + 120);
  c_box.bounds[0] = c_box.options[0].getGlobalBounds();

  c_box.options[1].setCharacterSize(16);
  c_box.options[1].setFillColor(sf::Color::Black);
  c_box.options[1].setString("2. Is this a trap by any chance?");
  c_box.options[1].setPosition(c_box.position.x + text_margin_x,c_box.options[0].getPosition().y + text_margin_y);
  c_box.bounds[1] = c_box.options[1].getGlobalBounds();

  c_box.options[2].setCharacterSize(16);
  c_box.options[2].setFillColor(sf::Color::Black);
  c_box.options[2].setString("3. No.");
  c_box.options[2].setPosition(c_box.position.x + text_margin_x,c_box.options[1].getPosition().y + text_margin_y);
  c_box.bounds[2] = c_box.options[2].getGlobalBounds();

  c_box.options[3].setCharacterSize(16);
  c_box.options[3].setFillColor(sf::Color::Black);
  c_box.options[3].setString("4. Leave the conversation");
  c_box.options[3].setPosition(c_box.position.x + text_margin_x,c_box.options[2].getPosition().y + text_margin_y);
  c_box.bounds[3] = c_box.options[3].getGlobalBounds();

  return c_box;
}

void draw_c_box(sf::RenderWindow &window,ConversationBox &c_box)
{
  window.draw(c_box.background);
  window.draw(c_box.message);
  for(int i = 0; i<c_box.options.size();i++)
  {
    window.draw(c_box.options[i]);
  }
}

void handle_option_click(ConversationBox &c_box)
{
  if(c_box.clicked[0])
  {
    std::cout << "Clicked option one" << std::endl;
  }
  else if(c_box.clicked[1])
  {
    std::cout << "Clicked option two" << std::endl;
  }
  else if(c_box.clicked[2])
  {
    std::cout << "Clicked option three" << std::endl;
  }
  else if(c_box.clicked[3])
  {
    std::cout << "Clicked option four" << std::endl;
  }
}

void detect_option_click(sf::Vector2f point,ConversationBox &c_box)
{
  if(c_box.bounds[0].contains(point))
  {
    c_box.clicked[0] = true;
    c_box.clicked[1] = false;
    c_box.clicked[2] = false;
    c_box.clicked[3] = false;
  }
  else if(c_box.bounds[1].contains(point))
  {
    c_box.clicked[0] = false;
    c_box.clicked[1] = true;
    c_box.clicked[2] = false;
    c_box.clicked[3] = false;
  }
  else if(c_box.bounds[2].contains(point))
  {
    c_box.clicked[0] = false;
    c_box.clicked[1] = false;
    c_box.clicked[2] = true;
    c_box.clicked[3] = false;
  }
  else if(c_box.bounds[3].contains(point))
  {
    c_box.clicked[0] = false;
    c_box.clicked[1] = false;
    c_box.clicked[2] = false;
    c_box.clicked[3] = true;
  }
}
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "RPG menu");
    window.setFramerateLimit(60);

    sf::Font font;
    Conversation c1;
    font.loadFromFile("PlayfairDisplay-VariableFont_wght.ttf");
    ConversationBox box = get_convo_box(font);

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

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
          sf::Vector2i position = sf::Mouse::getPosition(window);
          sf::Vector2f point = {position.x * 1.0f,position.y * 1.0f};
          detect_option_click(point,box);
          handle_option_click(box);
        }

        window.clear(sf::Color::White);
        draw_c_box(window,box);
        window.display();
    }

    return EXIT_SUCCESS;
}
