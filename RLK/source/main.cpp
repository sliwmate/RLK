#include <iostream>
#include "CGameEngine.h"

using namespace std;

int main(int argc, char** argv)
{
    CGameEngine gameEngine;
    if (gameEngine.init() < 1)
    {
        gameEngine.run();
    }
    system("pause");
    return 0;
}