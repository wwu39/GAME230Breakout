#pragma once
#include "Brick.h"
class Level
{
	Brick **bricks_matrix = nullptr;
public:
	Level(int);
	~Level();
};

