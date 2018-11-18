#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "Paddle.h"
#include "Level.h"

#define BALL_SPEED_INC 0.75f
#define BALL_RATE 5
#define BALL_R 30
#define BALL_CR 12
#define BALL_SPEED 5.0f

using namespace sf;

enum BallStatus { UNLAUNCHED, BOMB, MISL, BEAM };

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
	int exp_rate = EXP_RATE;
	Sound load_sound, hit_sound, expl_sound, blst_sound, bomb_sound, misl_sound, beam_sound;
	Vector2f velocity;

	void bullet_animate();
	void exp_animate();
public:
	static float speed_mult;
	BallStatus status = UNLAUNCHED;
	ExplosionStatus exp_status = NO_EXP;
	Ball();
	~Ball();

	void drawBullet(RenderWindow&);
	void drawExplosion(RenderWindow&);
	Vector2f getPosition();
	void setPosition(Vector2f pos);
	void update_state(float, Paddle&, vector<shared_ptr<Brick>>&);
};

