#pragma once
#include "Ball.h"
#include "Level.h"

#define RATE 5
#define GAMETILE "RailDefender 2: Breakout"

const Time dt = milliseconds(16);

enum GameStatus { RUNNING, ENDING, END };

class Breakout
{
	RectangleShape sky;
	RectangleShape rail;
	Paddle player;
	Ball bullet;
	Level * curLevel = nullptr;
	int LV = 1;
	int sky_move_frame = 120;
	int rate = RATE;
	void sky_animate();
	void update_state(float);
	void render_frame(RenderWindow&);
	GameStatus status = RUNNING;
	RectangleShape explosions[8];
	int expl_fr = 0;
	int expl_times = 0;
	int exp_rate = EXP_RATE;
	Sound expl_sound;
	Sound game_over;
	Text fin_game_over;
	Text fin_options;
	CircleShape fin_cursor;
	Sound fin_option_switch;
	Sound losing_bg;
public:
	Breakout();
	~Breakout();

#define EXIT 0
#define MENU 1
	int run(RenderWindow&);
};

