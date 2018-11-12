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

using namespace sf;

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
	static Font font;
	static SoundBuffer cannonfire;

	static void loadAssets();
};

