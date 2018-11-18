#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#define PADDLE_W 132.0f
#define PADDLE_H 148.0f
#define PADDLE_SPEED 500
#define PADDLE_RATE 5

using namespace sf;

enum PaddleStatus { WONDER = 0, START, FIRE };

class Paddle
{
	RectangleShape shape;
	RectangleShape shield;
	int curmvfr = 1;
	int curfrfr = 0;
	int curshfr = 0;
	bool reverse = false;
	bool shield_reverse = false;
	int rate = PADDLE_RATE;
	int shield_rate = SHIELD_RATE;
	Sound firingSound;
	int life = 5;
	Text lifepoint;

	void animate();
	void fire();
	void shield_flash();
public:
	PaddleStatus status = START;

	Paddle();
	~Paddle();

	void draw(RenderWindow&);
	Vector2f getPosition();
	void setPosition(Vector2f pos);
	void update_state(float);
	inline bool isDead() { return life <= 0; };

	friend class Ball;
};

