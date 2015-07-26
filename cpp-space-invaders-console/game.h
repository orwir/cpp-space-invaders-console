#pragma once

#include <ctime>
#include <vector>
#include "renderSystem.h"
#include "gameObject.h"
#include "level.h"

class Game
{
public:
    virtual void setupSystem();
    virtual void initialize();
    virtual bool frame();
    virtual void shutdown();

protected:
    virtual void render();
    virtual void update(float dt);

    GameObject* initializeObject(GameObject* object, GameObjectType type, float x, float y, char symbol, ConsoleColor color, ConsoleColor backgroundColor);
    void destroyObject(GameObject* object);
    
protected:
    bool m_isGameActive;
    clock_t m_clockLastFrame;
    RenderSystem m_renderSystem;
    int m_currentLevel;
    Level m_level;
    std::vector<GameObject*> m_objects;

};
