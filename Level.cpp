#include <sstream>
#include "Level.h"

#define MAX_BRICK 30;

int Level::score = 0;

Level::Level(int lv)
{
	int superlv = lv / 5 + 1;
	int sublv = lv % 5;
	if (sublv == 0) sublv = 5;
	time_remain = 110 + sublv * 10;
	if (time_remain < 60) time_remain = 60;
	for (int j = 0; j < sublv; ++j) for (int i = 0; i < 5; ++i) {
		int shield;
		int chance = rand() % 100;
		if (chance < 50) shield = 0;
		else if (chance >= 50 && chance < 80) shield = 1;
		else if (chance >= 80 && chance < 90) shield = 2;
		else shield = 3;
		brick_list.push_back(shared_ptr<Brick>(new Brick(shield, { float(120 + i * 140), float(100 + 70 * j) })));
	}
	level_bg.setBuffer(Assets::level_bg[sublv - 1]);
	win_level.setBuffer(Assets::win_level);
	level_title.setFont(Assets::font);
	level_title.setCharacterSize(200);
	level_title.setFillColor(Color::Green);
	level_title.setOrigin({ 215, 120 });
	level_title.setPosition({ 400, 300 });
	ostringstream str;
	str << superlv << " - " << sublv;
	level_title.setString(str.str());
	score_text.setFont(Assets::font);
	score_text.setCharacterSize(50);
	score_text.setFillColor(Color::Green);
	ostringstream str2;
	str2 << "Score: " << score;
	score_text.setString(str2.str());
	score_text.setPosition({ 5, -10 });
	time_text.setFont(Assets::font);
	time_text.setCharacterSize(50);
	time_text.setFillColor(Color::Green);
	time_text.setPosition({ 695, -10 }); 
	press_any_key.setFont(Assets::font);
	press_any_key.setCharacterSize(50);
	press_any_key.setFillColor(Color::Green);
	press_any_key.setPosition(100, 450);
	press_any_key.setString("Press Space to Continue...");
	fin_score.setFont(Assets::font);
	fin_score.setCharacterSize(75);
	fin_score.setFillColor(Color::Green);
	fin_score.setPosition({ 100, 100 });
}


Level::~Level()
{
	if (win_level.getStatus() == Sound::Playing) win_level.stop();
}

void Level::update_state(float dt) {
	if (status == NOT_CLEAR) {
		if (brick_list.empty()) {
			status = READY_TO_CLEAR;
			if (level_bg.getStatus() == Sound::Playing) level_bg.stop();
			win_level.play();
			ostringstream str;
			str << "Score:      " << score << endl;
			str << "Time Bonus:  " << time_remain * 19 << endl;
			score += (time_remain * 19);
			str << "Final Score:  " << score << endl;
			fin_score.setString(str.str());
		}
		for (auto i = brick_list.size() - 1; i != -1; --i) {
			if (brick_list[i]->status == DEAD) brick_list.erase(brick_list.begin() + i);
			else {
				if (brick_list[i]->status == DYING) { // give a random score
					score += brick_list[i]->score;
					ostringstream str;
					str << "Score: " << score;
					score_text.setString(str.str());
				}
				brick_list[i]->update_state(dt);
			}
		}
		++time_rate;
		if (time_rate / TIME_RATE) {
			if (time_remain > 0) {
				--time_remain;
				ostringstream str;
				str << "0" << time_remain / 60 << ":" << (time_remain % 60 > 9 ? "" : "0") << time_remain % 60;
				time_text.setString(str.str());
			} else {
				if (flashing) {
					time_text.setString("00:00");
					flashing = false;
				} else {
					time_text.setString("");
					flashing = true;
				}
			}
			time_rate = 0;
		}
	}
	else if (status == READY_TO_CLEAR) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) status = CLEAR;
	}
}

void Level::draw(RenderWindow& window) {
	for (auto &i : brick_list) i->draw(window);
	if (status == NOT_CLEAR || status == PREPARE) {
		window.draw(score_text);
		window.draw(time_text);
	}
	else if (status == READY_TO_CLEAR) {
		++flashRate;
		if (flashRate / 10) flashRate = 0;
		else window.draw(press_any_key);
		window.draw(fin_score);
	}
	if (status == PREPARE) {
		++flashRate;
		if (flashRate / 10) {
			flashRate = 0;
			++level_title_flashing_times;
			if (level_title_flashing_times == 4) {
				status = NOT_CLEAR;
				level_title_flashing_times = 0;
				flashRate = 0;
			}
		}
		else window.draw(level_title);
	}
}

bool Level::clear() {
	return status == CLEAR;
}
