#include "Assets.h"
#include "Paddle.h"

void Paddle::animate()
{
	shape.setTexture(&Assets::paddle_tex[curmvfr]);
	if (!reverse) ++curmvfr; else --curmvfr;
	if (curmvfr == 18) reverse = true;
	if (curmvfr == 0) reverse = false;
}

void Paddle::fire()
{
	shape.setTexture(&Assets::paddle_tex[curmvfr + 19]);
	++curfrfr;
	if (curfrfr == 5) { // explodsion ends
		status = WONDER;
		curfrfr = 0;
	}
}

Paddle::Paddle()
{
	shape.setSize({ 132, 148 });
	shape.setOrigin({ 66, 74 });
	shape.setTexture(&Assets::paddle_tex[0]);
	shape.setPosition(400, 564);
	firingSound.setBuffer(Assets::cannonfire);
}


Paddle::~Paddle()
{
}

void Paddle::draw(RenderWindow &window)
{
	++rate;
	if (rate / PADDLE_RATE) {
		if (status == WONDER || status == START) animate();
		if (status == FIRE) fire();
		rate = 0;
	}
	window.draw(shape);
}

Vector2f Paddle::getPosition()
{
	return shape.getPosition();
}

void Paddle::setPosition(Vector2f pos)
{
	shape.setPosition(pos);
}

void Paddle::move(float dt)
{
	Vector2f pos = shape.getPosition();
	if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && pos.x >= 53.f)
		pos.x -= PADDLE_SPEED * dt;
	if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Right)) && pos.x <= 747.f)
		pos.x += PADDLE_SPEED * dt;
	shape.setPosition(pos);
	if (status == START) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			status = FIRE;
			firingSound.play();
		}
	}
}
