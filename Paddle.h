#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#define PADDLE_SPEED 300
#define PADDLE_RATE 5

using namespace sf;

enum PaddleStatus { WONDER = 0, START, FIRE };

class Paddle
{
	RectangleShape shape;
	int curmvfr = 1;
	int curfrfr = 0;
	bool reverse = false;
	int rate = PADDLE_RATE;
	Sound firingSound;

	void animate();
	void fire();
public:
	PaddleStatus status = START;

	Paddle();
	~Paddle();

	void draw(RenderWindow&);
	Vector2f getPosition();
	void setPosition(float x, float y);
	void move(float);
};

