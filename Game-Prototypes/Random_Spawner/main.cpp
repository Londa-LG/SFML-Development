#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <chrono>

bool draw_rect(float percent,int x,int y)
{
  bool exist = false;
  int min = 1;
  int max = 50;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  std::minstd_rand0 generator(seed);
  std::uniform_int_distribution<int> distribution(min,max);
  float random_value = distribution(generator);

  float calc_percent = random_value / 50 * 100;
  std::cout << "random_value: " << random_value << std::endl;
  std::cout << "seed: " << seed << std::endl;

  if( calc_percent <= percent)
  {
    exist = true;
  }

  return exist;
}

void draw_world(sf::Vector2f windowSize, sf::Vector2f size, sf::RenderWindow &window)
{
  int y =0;
  sf::RectangleShape rect;

  rect.setSize(size);
  rect.setOutlineThickness(1);
  
  for(int y=0; y<windowSize.y; y +=size.x+1)
  {
    for(int x=0; x<windowSize.x; x +=size.x+1)
    {
      if(draw_rect(5,x,y))
      {
        rect.setPosition(x,y);
        rect.setFillColor(sf::Color::Black);
        rect.setOutlineColor(sf::Color::White);

        window.draw(rect);
      }
      else{
        rect.setPosition(x,y);
        rect.setFillColor(sf::Color::Yellow);
        rect.setOutlineColor(sf::Color::White);

        window.draw(rect);
      }
    }
  }
}

 
int main()
{
  sf::RenderWindow window(sf::VideoMode(800,600), "Window");
  window.setFramerateLimit(60);

  draw_world({800,600},{10,10},window);
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
          if(event.key.code == sf::Keyboard::Space)
          {
            draw_world({800,600},{10,10},window);
          }
        }
    }

      window.display();
  }

  return EXIT_SUCCESS;
}
