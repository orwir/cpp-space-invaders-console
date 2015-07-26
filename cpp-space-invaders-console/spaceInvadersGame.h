#pragma once

#include "game.h"
#include "spaceInvadersObjects.h"

enum SIObjectType : GameObjectType
{
    GameObjectType_Ship,
    GameObjectType_Bullet,
    GameObjectType_Alien
};

class SpaceInvaders : public Game
{
public:
    void initialize();

    void setShip(Ship* ship) { m_ship = ship; }
    Ship* getShip() { return m_ship; }

protected:
    void render();
    void update(float dt);

private:
    Ship* m_ship;
    float m_alienAmplitudeTime;
};
