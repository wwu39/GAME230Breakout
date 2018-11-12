#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#define BALL_SPEED 5.0f
#define BALL_SPEED_INC 0.75f
#define BALL_RATE 5

using namespace sf;

enum BallStatus { UNLAUNCHED, BOMB, MISL, BEAM, EXPL, BLST };

class Ball
{
	Shape &active = bomb;
	CircleShape bomb;
	CircleShape misl;
	CircleShape beam;
	RectangleShape expl;
	RectangleShape blst;
	int bomb_fr = 0, misl_fr = 0, beam_fr = 0, expl_fr = 0, blst_fr = 0;
	int rate = BALL_RATE;
	Sound load_sound, expl_sound, blst_sound, bomb_sound, misl_sound, beam_sound;
	Vector2f velocity;

	void animate();
public:
	BallStatus status = UNLAUNCHED;
	Ball();
	~Ball();

	void draw(RenderWindow&);
	Vector2f getPosition();
	void setPosition(Vector2f pos);
	void move(float);
};

