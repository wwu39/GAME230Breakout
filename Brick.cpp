#include "Brick.h"
Brick::Brick(int shieldLV, Vector2f pos)
{
	this->shieldLV = shieldLV;
	plane.setPosition(pos);
	shield.setPosition(pos);
}


Brick::~Brick()
{
}
