#pragma once
#include <memory>
#include <vector>
#include "Brick.h"

#define TIME_RATE 60

using namespace std;

enum LevelStatus { PREPARE = 0, NOT_CLEAR, READY_TO_CLEAR, CLEAR };

class Level
{
	Text score_text;
	int time_remain = 120;
	Text time_text;
	int time_rate = TIME_RATE;
	bool flashing = false;
	Text press_any_key;
	int flashRate = 10;
	Text fin_score;
	vector<shared_ptr<Brick>> brick_list;
	Text level_title;
	int level_title_flashing_times = 0;
	Sound level_bg;
	Sound win_level;
	int immortals = 0;
public:
	static int score;
	Level(int);
	~Level();
	void update_state(float);
	void draw(RenderWindow&);
	bool clear();
	LevelStatus status = PREPARE;
	friend class Breakout;
};

