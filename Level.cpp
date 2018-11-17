#include "Level.h"

#define MAX_BRICK 30;

Level::Level(int lv)
{
	for (int j = 0; j < 3; ++j) for (int i = 0; i < 5; ++i)
		brick_list.push_back(shared_ptr<Brick>(new Brick(0, { float(120 + i * 140), float(100 + 70 * j) })));
}


Level::~Level()
{
}

void Level::update_state(float dt) {
	for (auto i = brick_list.size() - 1; i != -1; --i) {
		if (brick_list[i]->status == DEAD) brick_list.erase(brick_list.begin() + i);
		else brick_list[i]->update_state(dt);
	}
}

void Level::draw(RenderWindow& window) {
	for (auto &i : brick_list) i->draw(window);
}

bool Level::clear() {
	return false;
}
