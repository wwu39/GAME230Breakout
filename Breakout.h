#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "Level.h"

#define RATE 5
#define GAMETILE "RailDefender 2: Breakout"

const Time dt = milliseconds(16);

class Breakout
{
	RectangleShape rail;
	Paddle player;
	Ball bullet;
	Level * curLevel = nullptr;

	void update_state(float);
	void render_frame(RenderWindow&);

public:
	Breakout();
	~Breakout();

#define EXIT 0
#define MENU 1
	int run(RenderWindow&);
};

