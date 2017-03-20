#include <iostream>

#include "game.h"

#ifdef __WIN32__
#  undef main
#endif

int main()
{
    CGame* Game = new CGame(800, 600);
    Game->MainLoop();
    delete Game;
    return 0;
}
