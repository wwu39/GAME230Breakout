#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "Assets.h"

#define BRICK_W 142.0f
#define BRICK_H 122.0f
#define BRICK_CW 140.0f
#define BRICK_CH 40
#define IDLE_RATE 5
#define WODDLE_RATE 5

using namespace sf;

enum BrickStatus { ALIVE = 0, DYING, DEAD };

class Brick
{
protected:
	RectangleShape plane;
	RectangleShape shield;
	int strengh;
	int shieldLV;
	int curshfr = 0;
	int shield_rate = SHIELD_RATE;
	bool shield_reverse = false;
	void shield_flash();
	int curidfr = 0;
	int idle_rate = 0;
	int idle_delay = 0;
	int RAND_IDLE_DELAY;
	bool idling = false;
	void idle();
	bool woddle_reverse = false;
	int woddle_y = 0;
	int woddle_up;
	int woddle_down;
	int woddle_rate = WODDLE_RATE;
	RectangleShape expl;
	RectangleShape blst;
	int expl_fr = 0, blst_fr = 0;
	int exp_rate= EXP_RATE;
	Sound expl_sound, blst_sound;
	void exp_animate();
public:
	Brick(int shieldLV, Vector2f pos);
	~Brick();
	void update_state(float);
	void draw(RenderWindow&);
	BrickStatus status = ALIVE;
	ExplosionStatus exp_status = NO_EXP;
	friend class Ball;
	friend class Breakout;
};

class MobileBrick :public Brick
{
	MobileBrick(int shieldLV, Vector2f pos) : Brick(shieldLV, pos) {};
	~MobileBrick();
};

