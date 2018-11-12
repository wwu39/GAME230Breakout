#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class Brick
{
	RectangleShape plane;
	RectangleShape shield;
	int shieldLV;
public:
	Brick(int shieldLV, Vector2f pos);
	~Brick();
	friend class Breakout;
};

