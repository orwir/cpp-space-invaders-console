#pragma once

#include "gameObject.h"

const float SHIP_SPEED = 35.0;
const float SHIP_FIRE_COOLDOWN = 0.2;

const float BULLET_SPEED = 40.0;

const float ALIEN_AMPLITUDE = 7.0;
const float ALIEN_SPEED = 0.23;

const unsigned char CellSymbol_Ship   = 'S';
const unsigned char CellSymbol_Bullet = '|';
const unsigned char CellSymbol_Alien  = 'X';

class Ship : public GameObject
{
public:
    Ship() : GameObject()
    {
        m_fireCooldownTime = 0.0;
    }

    void update(float dt)
    {
        GameObject::update(dt);
        if (getX() < 0)
        {
            setX(0);
        }
        else if (getX() > SCREEN_WIDTH - 1)
        {
            setX(SCREEN_WIDTH - 1);
        }
    }

    void setFireCooldown() { m_fireCooldownTime = SHIP_FIRE_COOLDOWN; }
    int getFireCooldown() { return m_fireCooldownTime; }

private:
    int m_fireCooldownTime;
};
