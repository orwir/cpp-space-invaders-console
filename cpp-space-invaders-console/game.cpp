#include "game.h"
#include <cstdlib>
#include <algorithm>

void Game::setupSystem()
{
    srand(time(0));
    m_isGameActive = true;
    m_clockLastFrame = 0;
    m_currentLevel = 0;
}

void Game::initialize()
{
    m_renderSystem.initialize();
}

bool Game::frame()
{
    clock_t clockNow = clock();
    clock_t deltaClock = clockNow - m_clockLastFrame;
    float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
    m_clockLastFrame = clockNow;

    render();
    update(deltaTime);

    return m_isGameActive;
}

void Game::shutdown()
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        delete m_objects[i];
    }
    m_objects.clear();
}

void Game::render()
{
    m_renderSystem.clear();

    for (int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->render(&m_renderSystem);
    }

    char buffer[SCREEN_WIDTH];
    int length = sprintf_s(buffer, "Objects: %d", m_objects.size());
    m_renderSystem.drawText(SCREEN_WIDTH - length, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);

    m_renderSystem.flush();
}

void Game::update(float dt)
{
    
}

GameObject* Game::initializeObject(GameObject* object, GameObjectType type, float x, float y, char symbol, ConsoleColor color, ConsoleColor backgroundColor)
{
    m_objects.push_back(object);

    object->setType(type);
    object->setX(x);
    object->setY(y);
    object->setSymbol(symbol);
    object->setColor(color);
    object->setBackgroundColor(backgroundColor);

    return object;
}

void Game::destroyObject(GameObject* object)
{
    m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}
