#pragma once

#include "screen.h"
#include "consoleColor.h"
#include "input.h"

static ConsoleColor GetSymbolColor(unsigned char symbol)
{
    switch (symbol)
    {
    case 'Y': return ConsoleColor_Yellow;
    case 'G': return ConsoleColor_Green;
    case 'B': return ConsoleColor_Black;
    case 'R': return ConsoleColor_Red;
    }
    return ConsoleColor_Black;
}

const unsigned char logoData[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                      G        YYY     YYY     YYY     GG            GGGGGGG    ",
    "                     GGG     YYYYYYYYYYYYYYYYYYYYYYYYY  GGG         GGGGGGGGG   ",
    "                     GGGG   YYYYYYYYYYYYYYYYYYYYYYYYYYY  GGG         GGGG  GGG  ",
    "                      GGGG   YYYYYYYYYYYYYYYYYYYYYYYYYY   GGGG       GGGG   GGG ",
    "          GGGGG        GGGG   YYYYYYYYYYYYYYYYYYYYYYYY     GGGG      GGGG   GGG ",
    "   G    GGGGGGGG       GGGG    YYYYYYYYYYYYYYYYYYYYYY       GGGG    GGGG    GG  ",
    "   GG  GGGG  GGG      GGGGG  GGGGGGGGGGGGGGGGGGGGGGGGGG     GGGGG  GGGGG    G   ",
    "   GGGGGG    GGGG   GGGGGG  GGGGGGGGGGGGGGGGGGGGGGGGGGGG    GGGGG GGGGG         ",
    "    GGGG    GGGG   GGGGGG  GGGGGRRRRRGGGGGGGGGGRRRRRGGGGG  GGGGGGGGGGG          ",
    "           GGGGGG GGGGGGGGGGGGGRRRRRRRGGGGGGGGRRRRRRRGGGGGGGGGGGGGGGG           ",
    "          GGGGGGGGGGGGGGGGGGGGGGRRRRRGGGGGGGGGGRRRRRGGGGGGGGGGGGGGGGGG          ",
    "         GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG         ",
    "        GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG        ",
    "       GGGGGGGGGGGGGGGGGGGGGGGGGBBBBBBBBBBBBBBBBBBBBGGGGGGGGGGGGGGGGGGGGG       ",
    "       GGGGGGGGGGGGGGGGGGGGGGGBBBBBBBBBBBBBBBBBBBBBBBBGGGGGGGGGGGGGGGGGGG       ",
    "       GGGGGGGGGGGGGGGGGGGGGGGBBBBBBBBBBBBBBBBBBBBBBBBGGGGGGGGGGGGGGGGGGG       ",
    "        GGGGGGGGGGGGGGGGGGGGGGGBBBBBBBBBBBBBBBBBBBBBBGGGGGGGGGGGGGGGGGGG        ",
    "         GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG         ",
    "           GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG           ",
    "             GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG             ",
    "                                                                                ",
    "                                                                                "
};

class Logo : public Screen
{
public:
    Logo() : Screen(4) {}

protected:
    void render() {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
            {
                getRenderSystem()->drawChar(x, y, logoData[y][x], GetSymbolColor(logoData[y][x]), ConsoleColor_Black);
            }
        }

        char buffer[SCREEN_WIDTH];
        int length = sprintf_s(buffer, "SPACE INVADERS");
        int x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, 1, buffer, ConsoleColor_Blue, ConsoleColor_Black);


        float loaded = getTotalTime() - getRemainedTime();
        float percent = loaded / getTotalTime();
        int fill = int(float(SCREEN_WIDTH) * percent);

        for (int i = 0; i <= fill; i++)
        {
            getRenderSystem()->drawChar(i, SCREEN_HEIGHT-1, ' ', ConsoleColor_DarkBlue, ConsoleColor_DarkBlue);
        }
    }
};

class Menu : public Screen
{

};

class LevelDivider : public Screen
{
public:
    LevelDivider() : Screen(3) {}

protected:
    const char* getText()
    {
        if (getRemainedTime() > 2)
        {
            return "Ready?";
        }
        else if (getRemainedTime() > 1)
        {
            return "Set...";
        }
        else
        {
            return "Go!";
        }
    }

    void render()
    {
        char buffer[SCREEN_WIDTH];
        int length = sprintf_s(buffer, "Level completed!");
        int x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2 - 1, buffer, ConsoleColor_White, ConsoleColor_Black);

        length = sprintf_s(buffer, getText());
        x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2 + 1, buffer, ConsoleColor_White, ConsoleColor_Black);
    }
};

class GameOver : public Screen
{
public:
    GameOver(Player* player) : Screen()
    {
        m_player = player;
    }
    
protected:
    void render()
    {
        char buffer[SCREEN_WIDTH];
        int length = sprintf_s(buffer, "GAME OVER");
        int x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2 - 2, buffer, ConsoleColor_White, ConsoleColor_Black);

        length = sprintf_s(buffer, "Your score: %d", m_player->getScore());
        x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2, buffer, ConsoleColor_Grey, ConsoleColor_Black);

        length = sprintf_s(buffer, "Press 'Q' to exit...");
        x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2 + 2, buffer, ConsoleColor_Grey, ConsoleColor_Black);
    }

    void update(float dt)
    {
        if (isKeyDown('Q'))
        {
            close();
        }
    }

private:
    Player* m_player;

};
