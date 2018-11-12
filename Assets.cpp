#include "Assets.h"

#include <sstream>

using namespace std;

Texture Assets::menu_bgtex;
Texture Assets::menu_ldtex;
Texture Assets::blast_tex[27];
Texture Assets::explode_tex[34];
Texture Assets::paddle_tex[38];
Texture Assets::rail_tex;
Texture Assets::bomb_tex[16];
Font Assets::font;
SoundBuffer Assets::cannonfire;

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

	// load font
	font.loadFromFile("fonts/menu.ttf");

	// load sound
	cannonfire.loadFromFile("sound/cannonfire.wav");
}
