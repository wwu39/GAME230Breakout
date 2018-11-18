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
	int score;
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
	RectangleShape expl[4];
	RectangleShape blst;
	int expl_fr[4] = { 0 }, blst_fr = 0;
	int exp_rate[4] = { EXP_RATE };
	Sound expl_sound, blst_sound;
	void exp_animate();
public:
	Brick(int shieldLV, Vector2f pos);
	~Brick();
	virtual void update_state(float);
	inline virtual bool isMobile() { return false; }
	virtual void draw(RenderWindow&);
	BrickStatus status = ALIVE;
	ExplosionStatus exp_status[4] = { NO_EXP };
	friend class Level;
	friend class Ball;
	friend class Breakout;
};

enum TurningStatus { NOT_TURNING, TURNING_LEFT, TURNING_RIGHT };

#define TURNING_RATE 5

class MobileBrick :public Brick
{
	Vector2f v = { 3.0f, 0.0f };
	TurningStatus turning_status = NOT_TURNING;
	int turning_rate = TURNING_RATE;
	int curtnfr = 0;
	void turnToLeft();
	void turnToRight();
public:
	MobileBrick(int shieldLV, Vector2f pos) : Brick(shieldLV, pos) {};
	~MobileBrick();
	void update_state(float);
	void draw(RenderWindow&);
	inline bool isMobile() { return true; }
};

