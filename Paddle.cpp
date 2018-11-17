#include <sstream>
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

void Paddle::shield_flash()
{
	shield.setTexture(&Assets::shield[WHITE][curshfr]);
	if (!shield_reverse) ++curshfr; else --curshfr;
	if (curshfr == 4) shield_reverse = true;
	if (curshfr == 0) shield_reverse = false;
}


Paddle::Paddle()
{
	shape.setSize({ PADDLE_W, PADDLE_H });
	shape.setOrigin({ PADDLE_W / 2.0f, PADDLE_H / 2.0f });
	shape.setTexture(&Assets::paddle_tex[0]);
	shape.setPosition(400, 564);
	shield.setSize({130, 130});
	shield.setOrigin({ 65, 65 });
	shield.setTexture(&Assets::shield[WHITE][0]);
	shield.setPosition(400, 564);
	firingSound.setBuffer(Assets::cannonfire);
	lifepoint.setFont(Assets::font);
	lifepoint.setCharacterSize(50);
	lifepoint.setFillColor(Color::Green);
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
	++shield_rate;
	if (shield_rate / SHIELD_RATE) {
		shield_flash();
		shield_rate = 0;
	}
	lifepoint.setPosition({ 1, 558 });
	if (life != 0) window.draw(lifepoint);
	lifepoint.setPosition({ 774, 558 });
	if (life != 0) window.draw(lifepoint);
	window.draw(shape);
	if (life != 0) window.draw(shield);
}

Vector2f Paddle::getPosition()
{
	return shape.getPosition();
}

void Paddle::setPosition(Vector2f pos)
{
	shape.setPosition(pos);
	shield.setPosition(pos);
}

void Paddle::update_state(float dt)
{
	Vector2f pos = shape.getPosition();
	if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && pos.x >= 53.f)
		pos.x -= PADDLE_SPEED * dt;
	if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Right)) && pos.x <= 747.f)
		pos.x += PADDLE_SPEED * dt;
	setPosition(pos);
	if (status == START) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (curmvfr == 0 || curmvfr == 1) curmvfr = 2;
			if (curmvfr == 18 || curmvfr == 17) curmvfr = 16;
			status = FIRE;
			firingSound.play();
		}
	}
	std::ostringstream str;
	str << life;
	if (life == 3 || life == 2) lifepoint.setFillColor(Color::Yellow);
	if (life == 1) lifepoint.setFillColor(Color::Red);
	lifepoint.setString(str.str());
}