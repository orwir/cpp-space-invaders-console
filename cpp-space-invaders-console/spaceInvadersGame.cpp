#include "spaceInvadersGame.h"
#include "spaceInvadersObjects.h"
#include "spaceInvadersScreens.h"
#include <cmath>

const float LEVEL_RESTART_COOLDOWN = 2;

GameObject* CreateGameObject(unsigned char symbol)
{
    switch (symbol)
    {
    case CellSymbol_Player:
        return new Player(3, SHIP_FIRE_COOLDOWN);
    case CellSymbol_Alien:
        return new Alien(1, 5);
    case CellSymbol_AlienSpread:
        return new Alien(2, 7);
    case CellSymbol_AlienBrood:
        return new Alien(1, 10);
    case CellSymbol_AlienTank:
        return new Alien(5, 11);
    }
    return 0;
}

void SpaceInvaders::initialize()
{
    if (getCurrentLevel() > 0)
    {
        LevelDivider* divider = new LevelDivider();
        divider->show();
        delete divider;
    }

    Game::initialize();

    Player* saved = m_player;
    m_player = 0;
    m_alienAmplitudeTime = 0.0;
    m_alienFireCooldown = ALIEN_FIRE_COOLDOWN;
    m_restartLevelCooldown = LEVEL_RESTART_COOLDOWN;

    LevelData levelData = getLevel()->getLevelData(getCurrentLevel());
    for (int row = 0; row < levelData.size(); row++)
    {
        for (int col = 0; col < levelData[row].size(); col++)
        {
            const unsigned char symbol = levelData[row][col];
            switch (symbol)
            {
            case CellSymbol_Player:
            {
                Player* player = (Player*)initializeObject(CreateGameObject(symbol), GameObjectType_Ship, col + 0.5, row,
                    getLevel()->getRenderCellSymbol(symbol),
                    getLevel()->getRenderCellSymbolColor(symbol),
                    getLevel()->getRenderCellSymbolBackgroundColor(symbol));
                setPlayer((Player*)player);
                if (saved != 0)
                {
                    player->setScore(saved->getScore());
                }
                break;
            }
            case CellSymbol_Alien:
            case CellSymbol_AlienSpread:
            case CellSymbol_AlienBrood:
            case CellSymbol_AlienTank:
            {
                GameObject* alien = initializeObject(CreateGameObject(symbol), GameObjectType_Alien, col + 0.5, row,
                    getLevel()->getRenderCellSymbol(symbol),
                    getLevel()->getRenderCellSymbolColor(symbol),
                    getLevel()->getRenderCellSymbolBackgroundColor(symbol));
                alien->setXSpeed(ALIEN_AMPLITUDE * cos(m_alienAmplitudeTime));
                alien->setYSpeed(ALIEN_SPEED);
                break;
            }
            }
        }
    }
}

void SpaceInvaders::render()
{
    Game::render();

    char buffer[SCREEN_WIDTH];
    int length = 0;

    length = sprintf_s(buffer, "Level: %d", getCurrentLevel() + 1);
    getRenderSystem()->drawText(0, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);

    length += 2;
    for (int i = 0; i < getPlayer()->getStrength(); i++)
    {
        getRenderSystem()->drawChar(length + i * 2, 0, 3, ConsoleColor_DarkRed, ConsoleColor_Black);
    }
    
    sprintf_s(buffer, "Score: %d", getPlayer()->getScore());
    getRenderSystem()->drawText(length + getPlayer()->getStrength() * 2 + 1, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);
}

void SpaceInvaders::update(float dt)
{
    if (isKeyDown(VK_LEFT))
    {
        getPlayer()->setXSpeed(-SHIP_SPEED);
    }
    else if (isKeyDown(VK_RIGHT))
    {
        getPlayer()->setXSpeed(SHIP_SPEED);
    }
    if (isKeyDown(VK_UP) && getPlayer()->getFireCooldown() <= 0)
    {
        getPlayer()->updateFireCooldown();
        GameObject* bullet = initializeObject(new Bullet(getPlayer()), GameObjectType_Bullet,
            getPlayer()->getX(), getPlayer()->getY() - 1,
            getLevel()->getRenderCellSymbol(CellSymbol_Bullet),
            getLevel()->getRenderCellSymbolColor(CellSymbol_Bullet),
            getLevel()->getRenderCellSymbolBackgroundColor(CellSymbol_Bullet));
        bullet->setYSpeed(-BULLET_SPEED);
    }
    if (isKeyDown('N') && m_restartLevelCooldown <= 0.0)
    {
        nextLevelOrEnd();
    }
    else if (m_restartLevelCooldown > 0)
    {
        m_restartLevelCooldown -= dt;
    }
    
    
    bool haveAliveAliens = false;

    for (int i = 0; i < getObjects().size(); i++)
    {
        GameObject* object = getObjects()[i];
        if (isDeleted(object))
        {
            continue;
        }

        object->update(dt);
        switch (object->getType())
        {
        case GameObjectType_Alien:
        {
            Alien* alien = (Alien*)object;
            haveAliveAliens = true;
            if (alien->getY() >= LEVEL_ROWS)
            {
                setGameActive(false);
            }
            else
            {
                alien->setXSpeed(ALIEN_AMPLITUDE * cos(m_alienAmplitudeTime));
            }
            break;
        }
        case GameObjectType_Bullet:
            if (object->getY() < 0 || object->getY() > SCREEN_HEIGHT)
            {
                planDelete(object);
            }
            else
            {
                for (int a = 0; a < getObjects().size(); a++)
                {
                    GameObject* subject = getObjects()[a];
                    if (isDeleted(subject))
                    {
                        continue;
                    }
                    if (object != subject && object->intersects(subject))
                    {
                        Bullet* bullet = (Bullet*)object;

                        if (subject->getType() == GameObjectType_Alien && bullet->getShooter()->getType() == GameObjectType_Ship) {
                            Alien* alien = (Alien*)subject;
                            Player* player = (Player*)bullet->getShooter();

                            if (alien->tryKill())
                            {
                                player->addScore(alien->getWorth());
                                planDelete(alien);
                            }
                            planDelete(bullet);
                        }
                        else if (subject->getType() == GameObjectType_Ship && bullet->getShooter()->getType() == GameObjectType_Alien)
                        {
                            Player* player = (Player*)subject;
                            Alien* alien = (Alien*)bullet->getShooter();
                            
                            if (player->tryKill())
                            {
                                planDelete(player);
                                setGameActive(false);
                            }
                            planDelete(bullet);
                        }
                        break;
                    }
                }
            }
            break;
        }
    }

    m_alienAmplitudeTime += dt;
    if (m_alienFireCooldown > 0)
    {
        m_alienFireCooldown -= dt;
    }
    else if (haveAliveAliens) {
        int index = rand() % getObjects().size();
        while (getObjects()[index]->getType() != GameObjectType_Alien)
        {
            index++;
            if (index >= getObjects().size())
            {
                index = 0;
            }
        }
        GameObject* alien = getObjects()[index];
        GameObject* bullet = initializeObject(new Bullet(alien), GameObjectType_Bullet,
            alien->getX(), alien->getY() + 1,
            getLevel()->getRenderCellSymbol(CellSymbol_Bullet),
            getLevel()->getRenderCellSymbolColor(CellSymbol_Bullet),
            getLevel()->getRenderCellSymbolBackgroundColor(CellSymbol_Bullet));
        bullet->setYSpeed(BULLET_SPEED);
        m_alienFireCooldown = ALIEN_FIRE_COOLDOWN;
    }

    if (!haveAliveAliens)
    {
        nextLevelOrEnd();
    }
}
