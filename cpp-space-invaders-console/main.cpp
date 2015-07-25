#include "spaceInvadersGame.h"

void main() {
    SpaceInvaders* game = new SpaceInvaders();

    game->setupSystem();
    game->initialize();
    
    while (game->frame());
    
    game->shutdown();

    delete game;
}