#include "Ball.h"

Ball::Ball()
{
}


Ball::~Ball()
{
}

void Ball::draw(RenderWindow &window)
{
	++rate;
	if (rate / BALL_RATE) animate();
	window.draw(active);
}

Vector2f Ball::getPosition()
{
	return active.getPosition();
}

void Ball::setPosition(Vector2f pos)
{
	active.setPosition(pos);
}

void Ball::move(float)
{
}

void Ball::animate()
{
	switch (status)
	{
	case UNLAUNCHED: {

	}
		break;
	case BOMB: {

	}
		break;
	case MISL: {

	}
		break;
	case BEAM: {

	}
		break;
	case EXPL: {

	}
		break;
	case BLST: {

	}
		break;
	}
}