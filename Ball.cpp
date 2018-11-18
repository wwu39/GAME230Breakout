#include <cmath>

#include "Assets.h"
#include "Ball.h"

#define PI 3.14159265358979323846f

float Ball::speed_mult = 1.0;

Ball::Ball()
{
	bomb.setRadius(BALL_R);
	bomb.setOrigin({ BALL_R, BALL_R });
	bomb.setTexture(&Assets::bomb_tex[0]);
	hit_sound.setBuffer(Assets::metalhit);
	load_sound.setBuffer(Assets::load);
	expl.setSize({ 120, 134 });
	expl.setOrigin({ 60, 67 });
	expl.setTexture(&Assets::explode_tex[0]);
	expl_sound.setBuffer(Assets::explosion);
}


Ball::~Ball()
{
}

void Ball::drawBullet(RenderWindow &window)
{
	++rate;
	if (rate / BALL_RATE) {
		bullet_animate();
		rate = 0;
	}
	if (status != UNLAUNCHED) window.draw(active);
}

void Ball::drawExplosion(RenderWindow &window)
{
	++exp_rate;
	if (exp_rate / EXP_RATE) {
		exp_animate();
		exp_rate = 0;
	}
	if (exp_status == EXPL) window.draw(expl);
	if (exp_status == BLST) window.draw(blst);
}

Vector2f Ball::getPosition()
{
	return active.getPosition();
}

void Ball::setPosition(Vector2f pos)
{
	active.setPosition(pos);
}

void Ball::update_state(float, Paddle& paddle, vector<shared_ptr<Brick>>& brick_list)
{
	if (status == UNLAUNCHED) {
		if (paddle.status != START) {
			float angle = paddle.curmvfr / 18.0f * PI;
			velocity = { -BALL_SPEED * speed_mult * cosf(angle), -BALL_SPEED * speed_mult * sinf(angle) };
			status = BOMB;
			active = bomb;
			setPosition(paddle.getPosition());
		}
	}
	if (status == BOMB || status == MISL || status == BEAM) {
		Vector2f pos = getPosition();
		// hit 4 walls
		if (pos.x < BALL_CR && velocity.x < 0) {
			velocity.x = -velocity.x;
			hit_sound.play();
		}
		if (pos.x > 800 - BALL_CR && velocity.x > 0) {
			velocity.x = -velocity.x;
			hit_sound.play();
		}
		if (pos.y < BALL_CR && velocity.y < 0) {
			velocity.y = -velocity.y;
			hit_sound.play();
		}
		// hit bricks
		for (auto i = brick_list.size() - 1; i != -1; --i) {
			if (brick_list[i]->status == ALIVE) {
				Vector2f brick_pos = brick_list[i]->plane.getPosition();
				if (pos.x > brick_pos.x - BRICK_CW / 2.0f && pos.x < brick_pos.x + BRICK_CW / 2.0f
					&& ((pos.y > brick_pos.y && pos.y - BALL_CR - BRICK_CH / 2.0f < brick_pos.y && velocity.y < 0)
						|| (pos.y < brick_pos.y && pos.y + BALL_CR + BRICK_CH / 2.0f > brick_pos.y && velocity.y > 0))) { // hit top or bottom
					velocity.y = -velocity.y; // flip vy
					if (brick_list[i]->shieldLV) { // damage
						brick_list[i]->exp_status[brick_list[i]->shieldLV] = EXPL;
						brick_list[i]->expl_sound.play();
						Assets::nullify.play();
						brick_list[i]->expl[brick_list[i]->shieldLV].setPosition(pos);
						--brick_list[i]->shieldLV;
					}
					else { // kill
						brick_list[i]->status = DYING;
						brick_list[i]->exp_status[0] = EXPL;
						expl_sound.play();
						brick_list[i]->expl[0].setPosition(brick_pos);
						brick_list[i]->plane.setPosition({-100, -100});
					}
				}
				else if (pos.y > brick_pos.y - BRICK_CH / 2.0f && pos.y < brick_pos.y + BRICK_CH / 2.0f
					&& ((pos.x < brick_pos.x && pos.x + BALL_CR + BRICK_CW / 2.0f > brick_pos.x && velocity.x > 0)
						|| (pos.x > brick_pos.x && pos.x - BALL_CR - BRICK_CW / 2.0f < brick_pos.x && velocity.x < 0))) { // hit left or right
					velocity.x = -velocity.x; // flip vx
					if (brick_list[i]->shieldLV) { // damage
						brick_list[i]->exp_status[brick_list[i]->shieldLV] = EXPL;
						brick_list[i]->expl_sound.play();
						Assets::nullify.play();
						brick_list[i]->expl[brick_list[i]->shieldLV].setPosition(pos);
						--brick_list[i]->shieldLV;
					}
					else { // kill
						brick_list[i]->status = DYING;
						brick_list[i]->exp_status[0] = EXPL;
						expl_sound.play();
						brick_list[i]->expl[0].setPosition(brick_pos);
						brick_list[i]->plane.setPosition({ -100, -100 });
					}
				}
			}
		}

		// hit paddle
		Vector2f ppos = paddle.getPosition();
		if (pos.x > ppos.x - PADDLE_W / 2.0f && pos.x < ppos.x + PADDLE_W / 2.0f && pos.y > ppos.y - BALL_CR && velocity.y > 0) {
			// velocity.y = -velocity.y;
			// float angle = acos(-velocity.x / sqrt(velocity.x * velocity.x + velocity.y * velocity.y));
			float angle = (pos.x - (ppos.x - PADDLE_W / 2.0f - 20)) / (PADDLE_W + 40) * PI;
			velocity = { -BALL_SPEED * speed_mult * cosf(angle), -BALL_SPEED * speed_mult * sinf(angle) };

			paddle.curmvfr = int(angle * 18.0f / PI);
			load_sound.play();
			paddle.status = FIRE;
			paddle.firingSound.play();
		}

		// hit the rail
		if (pos.y >= 564 && velocity.y > 0) {
			status = UNLAUNCHED;
			exp_status = EXPL;
			expl_sound.play();
			expl.setPosition(pos);
			load_sound.play();
			paddle.status = START;
			--paddle.life;
		}

		// update position
		pos += velocity;
		setPosition(pos);
	}
}

void Ball::bullet_animate()
{
	switch (status)
	{
	case UNLAUNCHED: {

	}
		break;
	case BOMB: {
		bomb.setTexture(&Assets::bomb_tex[bomb_fr]);
		bomb_fr = (bomb_fr + 1) % 16;
	}
		break;
	case MISL: {

	}
		break;
	case BEAM: {

	}
		break;
	}
}

void Ball::exp_animate()
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