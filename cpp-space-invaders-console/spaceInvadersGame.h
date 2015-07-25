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
    bool frame()
    {
        clock_t clockNow = clock();
        clock_t deltaClock = clockNow - m_clockLastFrame;
        float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
        m_clockLastFrame = clockNow;

        render();
        update(deltaTime);

        return m_isGameActive;
    }

    void setShip(Ship* ship) { m_ship = ship; }
    Ship* getShip() { return m_ship; }

protected:
    void update(float dt);

private:
    Ship* m_ship;
    float m_alienAmplitudeTime;
};
