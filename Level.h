#pragma once
#include <memory>
#include <vector>
#include "Brick.h"

using namespace std;

enum LevelStatus { NOT_CLEAR = 0, READY_TO_CLEAR, CLEAR };

class Level
{
	vector<shared_ptr<Brick>> brick_list;
public:
	Level(int);
	~Level();
	void update_state(float);
	void draw(RenderWindow&);
	bool clear();
	LevelStatus status = NOT_CLEAR;
	friend class Breakout;
};

