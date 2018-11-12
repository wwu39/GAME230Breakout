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
protected:
	RectangleShape plane;
	RectangleShape shield;
	int strength;
public:
	Brick(int shieldLV, Vector2f pos);
	~Brick();
	void takeDamage();
	friend class Breakout;
};

class MobileBrick :public Brick
{
	MobileBrick(int shieldLV, Vector2f pos) : Brick(shieldLV, pos) {};
	~MobileBrick();
};

