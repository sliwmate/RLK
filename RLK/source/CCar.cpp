#include "CCar.h"

CCar::CCar(): CRigidbody::CRigidbody()
{
	wheelF = NULL;
	wheelR = NULL;
}

CCar::CCar(float x, float y, const char* spritePath) :
	CRigidbody::CRigidbody(x, y, spritePath)
{
}
