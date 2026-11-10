#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Helpers.h"
#include "Settings.h" 
#include "Gameplay.h"
#include "Game.h"

int main()
{
    Game game = Game();

    game.run();

    return EXIT_SUCCESS;
}
