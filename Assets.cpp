#include "Assets.h"

#include <sstream>

using namespace std;

Texture Assets::menu_bgtex;
Texture Assets::menu_ldtex;
Texture Assets::blast_tex[27];
Texture Assets::explode_tex[34];
Texture Assets::paddle_tex[38];
Texture Assets::shield[4][5];
Texture Assets::rail_tex;
Texture Assets::bomb_tex[16];
Texture Assets::sky_tex;
Texture Assets::plane[16];
Texture Assets::plane_t[13];
Font Assets::font;
SoundBuffer Assets::cannonfire;
SoundBuffer Assets::metalhit;
SoundBuffer Assets::load;
SoundBuffer Assets::explosion;
SoundBuffer Assets::gameover;
SoundBuffer Assets::option;
SoundBuffer Assets::title;
SoundBuffer Assets::shield_nullify;
Sound Assets::nullify;
SoundBuffer Assets::win_level;
SoundBuffer Assets::level_bg[5];
SoundBuffer Assets::losing;
SoundBuffer Assets::menu_bg;
SoundBuffer Assets::button;
Sound Assets::button_press;
SoundBuffer Assets::under_attack;
SoundBuffer Assets::critical_damaged;
SoundBuffer Assets::rail_destroyed;
SoundBuffer Assets::rail_repair;
int Assets::expl_idx = 0;

Assets::Assets()
{
}


Assets::~Assets()
{
}

void Assets::loadAssets()
{
	// load menu files
	menu_bgtex.loadFromFile("sprites/menu.png");
	menu_ldtex.loadFromFile("sprites/loading.png");

	// load game assets
	for (int i = 0; i < 27; ++i) { // blast
		ostringstream filename;
		filename << "sprites/blast 00" << (i > 9 ? "" : "0") << i << ".png";
		blast_tex[i].loadFromFile(filename.str());
	}
	for (int i = 0; i < 34; ++i) { // explosion
		ostringstream filename;
		filename << "sprites/explode 00" << (i > 9 ? "" : "0") << i << ".png";
		explode_tex[i].loadFromFile(filename.str());
	}
	for (int i = 0; i < 38; ++i) { // paddle animation
		ostringstream filename;
		filename << "sprites/paddle 00" << (i > 9 ? "" : "0") << i << ".png";
		paddle_tex[i].loadFromFile(filename.str());
	}
	rail_tex.loadFromFile("sprites/rail.png"); // rail
	for (int i = 0; i < 16; ++i) { // bomb animation
		ostringstream filename;
		filename << "sprites/bomb 00" << (i > 9 ? "" : "0") << i << ".png";
		bomb_tex[i].loadFromFile(filename.str());
	}
	for (int i = 0; i < 5; ++i) { // white shield animation
		ostringstream filename;
		filename << "sprites/shield_white 000" << i << ".png";
		shield[WHITE][i].loadFromFile(filename.str());
	}
	for (int i = 0; i < 5; ++i) { // red shield animation
		ostringstream filename;
		filename << "sprites/shield_red 000" << i << ".png";
		shield[RED][i].loadFromFile(filename.str());
	}
	for (int i = 0; i < 5; ++i) { // blue shield animation
		ostringstream filename;
		filename << "sprites/shield_blue 000" << i << ".png";
		shield[BLUE][i].loadFromFile(filename.str());
	}
	for (int i = 0; i < 5; ++i) { // green shield animation
		ostringstream filename;
		filename << "sprites/shield_green 000" << i << ".png";
		shield[GREEN][i].loadFromFile(filename.str());
	}
	sky_tex.loadFromFile("sprites/sky.png");
	for (int i = 0; i < 16; ++i) {
		ostringstream filename;
		filename << "sprites/plane 00" << (i > 9 ? "" : "0") << i << ".png";
		plane[i].loadFromFile(filename.str());
	}
	for (int i = 0; i < 13; ++i) {
		ostringstream filename;
		filename << "sprites/plane_tl 00" << (i > 9 ? "" : "0") << i << ".png";
		plane_t[i].loadFromFile(filename.str());
	}


	// load font
	font.loadFromFile("fonts/menu.ttf");

	// load sound
	cannonfire.loadFromFile("sound/cannonfire.wav");
	metalhit.loadFromFile("sound/metalhit.wav");
	load.loadFromFile("sound/load.wav");
	explosion.loadFromFile("sound/explosion.wav");
	gameover.loadFromFile("sound/gameover.wav");
	option.loadFromFile("sound/option.wav");
	title.loadFromFile("sound/title.wav");
	shield_nullify.loadFromFile("sound/nullify.wav");
	nullify.setBuffer(shield_nullify);
	win_level.loadFromFile("sound/win_level.wav");
	for (int i = 0; i < 5; ++i) {
		ostringstream filename;
		filename << "sound/b0" << i + 1 << ".wav";
		level_bg[i].loadFromFile(filename.str());
	}
	losing.loadFromFile("sound/losing_bg.wav");
	menu_bg.loadFromFile("sound/menu_bg.wav");
	button.loadFromFile("sound/button.wav");
	button_press.setBuffer(button);
	under_attack.loadFromFile("sound/under_attack.wav");
	critical_damaged.loadFromFile("sound/critical_damage.wav");
	rail_destroyed.loadFromFile("sound/rail_destroyed.wav");
	rail_repair.loadFromFile("sound/repair.wav");
}
