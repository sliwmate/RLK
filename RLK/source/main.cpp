#include <iostream>
#include "CGameEngine.h"
#include "CCommon.h"

using namespace std;

int main(int argc, char** argv)
{
    CGameEngine gameEngine;
    if (gameEngine.init() < 1)
    {
        gameEngine.run();
    }
    // Test Comment from Krakowska
    system("pause");
    return 0;
}