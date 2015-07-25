#include "level.h"
#include "spaceInvadersObjects.h"
#include <array>

unsigned char Level::getRenderCellSymbol(unsigned char cellSymbol)
{
    switch (cellSymbol)
    {
    case CellSymbol_Ship:   return 202;
    case CellSymbol_Alien:  return 2;
    case CellSymbol_Bullet: return 179;
    }
}

ConsoleColor Level::getRenderCellSymbolColor(unsigned char cellSymbol)
{
    switch (cellSymbol)
    {
    case CellSymbol_Ship:   return ConsoleColor_White;
    case CellSymbol_Alien:  return ConsoleColor_Green;
    case CellSymbol_Bullet: return ConsoleColor_Red;
    }
}

ConsoleColor Level::getRenderCellSymbolBackgroundColor(unsigned char cellSymbol)
{
    switch (cellSymbol)
    {
    case CellSymbol_Ship:   return ConsoleColor_DarkGrey;
    }
    return ConsoleColor_Black;
}

LevelData levelData0 = {
    "                                                                                ",
    "       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       ",
    "         X  XXXX XX XXXXXXX  XXXXXXXXXXXXXXXXXXXXXX  XXXXXXX XX XXXX  X         ",
    "       XXXXXXXXX    X  X  X  X  XXX  XXXXXX  XXX  X  X  X  X    XXXXXXXXX       ",
    "            XXXX    X  X  X  XXXXXXX  XXXX  XXXXXXX  X  X  X    XXXX            ",
    "            XXXX             X   XXXXXXXXXXXXXX   X             XXXX            ",
    "            X  X                  XXXXXXXXXXXX                  X  X            ",
    "                                  XX  XXXX  XX                                  ",
    "                                  XX  X  X  XX                                  ",
    "                                  X          X                                  ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                       S                                        ",
};

LevelData Level::getLevelData(int level)
{
    switch (level)
    {
    case 0: return levelData0;
    }
    return levelDataEmpty;
}
