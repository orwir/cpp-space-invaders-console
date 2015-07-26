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
        m_lives = 3;
        m_score = 0;
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
        if (m_fireCooldownTime > 0)
        {
            m_fireCooldownTime -= dt;
        }
    }

    void setFireCooldown() { m_fireCooldownTime = SHIP_FIRE_COOLDOWN; }
    float getFireCooldown() { return m_fireCooldownTime; }

    int getLives() { return m_lives; }
    bool tryKill() { return --m_lives <= 0; }

    int getScore() { return m_score; }
    void addScore(int score) { m_score += score; }

private:
    float m_fireCooldownTime;
    int m_lives;
    int m_score;
};

class Alien : public GameObject
{
public:
    Alien(int strength, int worth) : GameObject()
    {
        m_strength = strength;
        m_worth = worth;
    }

    int getStrength() { return m_strength; }
    bool tryKill() { return ((--m_strength) <= 0); }

    int getWorth() { return m_worth; }

private:
    int m_strength;
    int m_worth;
};

class Bullet : public GameObject
{
public:
    Bullet(GameObject* shooter) : GameObject()
    {
        m_shooter = shooter;
    }

    GameObject* getShooter() { return m_shooter; }

private:
    GameObject* m_shooter;
};
