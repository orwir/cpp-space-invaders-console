#pragma once

#include "gameObject.h"
#include <cmath>

const float SHIP_SPEED = 35.0;
const float SHIP_FIRE_COOLDOWN = 0.2;

const float BULLET_SPEED = 40.0;

const float ALIEN_AMPLITUDE = 7.0;
const float ALIEN_SPEED = 0.18;
const float ALIEN_FIRE_COOLDOWN = 2.08;

const unsigned char CellSymbol_Player      = 'P';
const unsigned char CellSymbol_Bullet      = '|';
const unsigned char CellSymbol_Alien       = 'X';
const unsigned char CellSymbol_AlienSpread = 'S';
const unsigned char CellSymbol_AlienBrood  = 'B';
const unsigned char CellSymbol_AlienTank   = 'T';

class Ship : public GameObject
{
public:
    Ship(int strength)
    {
        m_strength = strength;
    }

    void update(float dt)
    {
        GameObject::update(dt);
    }

    int getStrength() { return m_strength; }
    void setStrength(int strength) { m_strength = strength; }
    bool tryKill() { return ((--m_strength) <= 0); }

private:
    int m_strength;
};

class Player : public Ship
{
public:
    Player(int strength, float fireCooldown) : Ship(strength)
    {
        m_score = 0;
        m_fireCooldown = fireCooldown;
        m_currentFireCooldown = 0;
    }

    void update(float dt)
    {
        Ship::update(dt);
        if (getX() < 0)
        {
            setX(0);
        }
        else if (getX() > SCREEN_WIDTH - 1)
        {
            setX(SCREEN_WIDTH - 1);
        }
        if (m_fireCooldown > 0)
        {
            m_currentFireCooldown -= dt;
        }
    }

    int getScore() { return m_score; }
    void setScore(int score) { m_score = score; }
    void addScore(int score) { m_score += score; }

    float getFireCooldown() { return m_currentFireCooldown; }
    void updateFireCooldown() { m_currentFireCooldown = m_fireCooldown; }

private:
    int m_score;
    float m_fireCooldown;
    float m_currentFireCooldown;
};

class Alien : public Ship
{
public:
    Alien(int strength, int worth) : Ship(strength)
    {
        m_worth = worth;
    }

    int getWorth() { return m_worth; }

private:
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
