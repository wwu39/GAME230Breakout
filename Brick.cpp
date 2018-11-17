#include "Brick.h"

Brick::Brick(int shieldLV, Vector2f pos)
{
	this->shieldLV = shieldLV;
	plane.setSize({ BRICK_W, BRICK_H });
	plane.setOrigin({ BRICK_W / 2.0f, BRICK_H / 2.0f });
	plane.setTexture(&Assets::plane[0]);
	plane.setPosition(pos);
	shield.setSize({ 130, 130 });
	shield.setOrigin({ 65, 65 });
	shield.setTexture(&Assets::shield[shieldLV][0]);
	shield.setPosition(pos);
	RAND_IDLE_DELAY = (32 + rand() % 16) * IDLE_RATE;
	woddle_up = 1 + rand() % 5;
	woddle_down = rand() % 5 - 5;
	expl.setSize({ 120, 134 });
	expl.setOrigin({ 60, 67 });
	expl.setTexture(&Assets::explode_tex[0]);
	expl_sound.setBuffer(Assets::explosion);
}

void Brick::shield_flash()
{
	shield.setTexture(&Assets::shield[shieldLV][curshfr]);
	if (!shield_reverse) ++curshfr; else --curshfr;
	if (curshfr == 4) shield_reverse = true;
	if (curshfr == 0) shield_reverse = false;
}

void Brick::exp_animate()
{
	switch (exp_status)
	{
	case NO_EXP: {

	}
				 break;
	case EXPL: {
		expl.setTexture(&Assets::explode_tex[expl_fr]);
		++expl_fr;
		if (expl_fr == 34) {
			exp_status = NO_EXP;
			if (status == DYING) status = DEAD;
			expl_fr = 0;
			expl.setTexture(&Assets::explode_tex[expl_fr]);
		}
	}
			   break;
	case BLST: {

	}
			   break;
	}
}

Brick::~Brick()
{
}

void Brick::update_state(float)
{
	if (status == ALIVE) {
		++woddle_rate;
		if (woddle_rate / WODDLE_RATE) {
			plane.setOrigin({ BRICK_W / 2.0f, BRICK_H / 2.0f + float(woddle_y) });
			if (!woddle_reverse) ++woddle_y; else --woddle_y;
			if (woddle_y == woddle_up) {
				woddle_reverse = true;
				woddle_up = 1 + rand() % 5;
			}
			if (woddle_y == woddle_down) {
				woddle_reverse = false;
				woddle_down = rand() % 5 - 5;
			}
			woddle_rate = 0;
		}
	}
}

void Brick::draw(RenderWindow& window)
{
	++shield_rate;
	if (shield_rate / SHIELD_RATE) {
			shield_flash();
			shield_rate = 0;
	}
	if (idling) {
		++idle_rate;
		if (idle_rate / IDLE_RATE) {
			idle();
			idle_rate = 0;
		}
	} else {
		++idle_delay;
		if (idle_delay / RAND_IDLE_DELAY) {
			idling = true;
			idle_delay = 0;
			RAND_IDLE_DELAY = (32 + rand() % 160) * IDLE_RATE;
		}
	}
	if (status == ALIVE) window.draw(plane);
	if (shieldLV) window.draw(shield);
	++exp_rate;
	if (exp_rate / EXP_RATE) {
		exp_animate();
		exp_rate = 0;
	}
	if (exp_status == EXPL) window.draw(expl);
	if (exp_status == BLST) window.draw(blst);
}

void Brick::idle()
{
	plane.setTexture(&Assets::plane[curidfr]);
	++curidfr;
	if (curidfr == 16) { 
		idling = false;
		curidfr = 0;
		plane.setTexture(&Assets::plane[curidfr]);
	}
}

MobileBrick::~MobileBrick()
{
}
