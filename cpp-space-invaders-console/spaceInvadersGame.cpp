#include "spaceInvadersGame.h"
#include "input.h"
#include <cmath>

void SpaceInvaders::initialize()
{
    Game::initialize();

    m_alienAmplitudeTime = 0.0;

    LevelData levelData = m_level.getLevelData(m_currentLevel);
    for (int row = 0; row < levelData.size(); row++)
    {
        for (int col = 0; col < levelData[row].size(); col++)
        {
            const unsigned char symbol = levelData[row][col];
            switch (symbol)
            {
            case CellSymbol_Ship:
            {
                GameObject* ship = initializeObject(new Ship(), GameObjectType_Ship, col + 0.5, row,
                    m_level.getRenderCellSymbol(symbol),
                    m_level.getRenderCellSymbolColor(symbol),
                    m_level.getRenderCellSymbolBackgroundColor(symbol));
                setShip((Ship*)ship);
                break;
            }
            case CellSymbol_Alien:
            {
                GameObject* alien = initializeObject(new GameObject(), GameObjectType_Alien, col + 0.5, row,
                    m_level.getRenderCellSymbol(symbol),
                    m_level.getRenderCellSymbolColor(symbol),
                    m_level.getRenderCellSymbolBackgroundColor(symbol));
                alien->setXSpeed(ALIEN_AMPLITUDE * cos(m_alienAmplitudeTime));
                alien->setYSpeed(ALIEN_SPEED);
                break;
            }
            }
        }
    }
}

void SpaceInvaders::update(float dt)
{
    bool haveAliveAliens = false;

    for (int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->update(dt);
        switch (m_objects[i]->getType())
        {
        case GameObjectType_Alien:
            haveAliveAliens = true;
            if (m_objects[i]->getY() >= LEVEL_ROWS)
            {
                m_isGameActive = false;
            }
            else
            {
                m_objects[i]->setXSpeed(ALIEN_AMPLITUDE * cos(m_alienAmplitudeTime));
            }
            break;

        case GameObjectType_Bullet:
            if (m_objects[i]->getY() < 0)
            {
                destroyObject(m_objects[i]);
            }
            else
            {
                for (int a = 0; a < m_objects.size(); a++)
                {
                    if (m_objects[i]->intersects(m_objects[a]))
                    {
                        destroyObject(m_objects[i]);
                        destroyObject(m_objects[a]);
                        break;
                    }
                }
            }
            break;
        }
    }

    m_alienAmplitudeTime += dt;

    if (!haveAliveAliens)
    {
        m_isGameActive = false;
    }

    if (isKeyDown(VK_LEFT))
    {
        getShip()->setXSpeed(-SHIP_SPEED);
    }
    else if (isKeyDown(VK_RIGHT))
    {
        getShip()->setXSpeed(SHIP_SPEED);
    }
    if (isKeyDown(VK_UP) && getShip()->getFireCooldown() <= 0)
    {
        getShip()->setFireCooldown();
        GameObject* bullet = initializeObject(new GameObject(), GameObjectType_Bullet,
            getShip()->getX(), getShip()->getY() - 1,
            m_level.getRenderCellSymbol(CellSymbol_Bullet),
            m_level.getRenderCellSymbolColor(CellSymbol_Bullet),
            m_level.getRenderCellSymbolBackgroundColor(CellSymbol_Bullet));
        bullet->setYSpeed(-BULLET_SPEED);
    }
}
