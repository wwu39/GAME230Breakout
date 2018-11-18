#pragma once
/*
                              Assets Class used to load all game assets
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#define SHIELD_RATE 10
#define WHITE 0
#define RED 1
#define BLUE 2
#define GREEN 3
#define EXP_RATE 5

using namespace sf;

enum ExplosionStatus { NO_EXP, EXPL, BLST };

class Assets
{
	Assets(); // can initiate an object
public:
	~Assets();

	static Texture menu_bgtex;
	static Texture menu_ldtex;
	static Texture blast_tex[27];
	static Texture explode_tex[34];
	static Texture paddle_tex[38];
	static Texture rail_tex;
	static Texture bomb_tex[16];
	static Texture shield[4][5];
	static Texture sky_tex;
	static Texture plane[16];
	static Font font;
	static SoundBuffer cannonfire;
	static SoundBuffer metalhit;
	static SoundBuffer load;
	static SoundBuffer explosion;
	static SoundBuffer gameover;
	static SoundBuffer option;
	static SoundBuffer title;
	static SoundBuffer shield_nullify;
	static Sound nullify;
	static SoundBuffer win_level;
	static SoundBuffer level_bg[5];
	static SoundBuffer losing;
	static SoundBuffer menu_bg;
	static SoundBuffer button;
	static Sound button_press;

	static void loadAssets();
};

