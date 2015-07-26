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

    void setPlayer(Player* player) { m_player = player; }
    Player* getPlayer() { return m_player; }

protected:
    void render();
    void update(float dt);

private:
    Player* m_player = 0;
    float m_alienAmplitudeTime;
    float m_alienFireCooldown;
    float m_restartLevelCooldown;
};
