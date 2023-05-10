#include <iostream>
#include "CGameEngine.h"
#include "CPhysics.h"

using namespace std;

int main(int argc, char** argv)
{
    /*CGameEngine gameEngine;
    if (gameEngine.init() < 1)
    {
        gameEngine.run();
    }
    */
    CPhysics::CVector2<int> a(1,2);
    CPhysics::CVector2<int> b(220, 1);
    std::cout << "Vector A: " << a.x << ", " << a.y << std::endl;
    a += b;
    std::cout << "Vector A+B: " << a.x << ", " << a.y << std::endl;
    a = -a;
    std::cout << "Vector -(A+B): " << a.x << ", " << a.y << std::endl;
    a.setAngle(-3.14f);
    std::cout << "Vector -(A+B): " << a.x << ", " << a.y << std::endl;
    std::cout << "Angle: " << a.getAngle() << std::endl;
    system("pause");
    return 0;
}