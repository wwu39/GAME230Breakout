#include "Brick.h"
Brick::Brick(int shieldLV, Vector2f pos)
{
	strength = shieldLV;
	plane.setPosition(pos);
	shield.setPosition(pos);
}


Brick::~Brick()
{
}

void Brick::takeDamage()
{
	if (strength > 0) --strength;
	else delete this;
}

MobileBrick::~MobileBrick()
{
}
