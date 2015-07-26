#include "spaceInvadersGame.h"
#include "spaceInvadersScreens.h"

float randomCooldownTest(float min, float max)
{
    return ((max - min)*((float)rand() / RAND_MAX)) + min;
}

void main() {
    Screen* logo = new Logo();
    logo->show();
    delete logo;
    
    SpaceInvaders* game = new SpaceInvaders();

    game->setupSystem();
    game->initialize();
    
    while (game->frame());

    Screen* end = new GameOver(game->getPlayer());
    end->show();
    delete end;
    
    game->shutdown();
    delete game;
}
