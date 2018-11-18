#include <sstream>

#include "Assets.h"
#include "Breakout.h"

Breakout::Breakout()
{
	rail.setSize({ 800, 28 });
	rail.setOrigin({ 400, 14 });
	rail.setTexture(&Assets::rail_tex);
	rail.setPosition(400, 564);
	sky.setSize({ 800, 600 });
	sky.setTexture(&Assets::sky_tex);
	for (int i = 0; i < 8; ++i) {
		explosions[i].setSize({ 120, 134 });
		explosions[i].setOrigin({ 60, 67 });
		explosions[i].setPosition({ 50.0f + 100.0f * i, 576 });
		explosions[i].setTexture(&Assets::explode_tex[0]);
	}
	expl_sound.setBuffer(Assets::explosion);
	game_over.setBuffer(Assets::gameover);
	fin_game_over.setFont(Assets::font);
	fin_game_over.setCharacterSize(100);
	fin_game_over.setFillColor(Color::Green);
	fin_game_over.setLineSpacing(0.75);
	fin_game_over.setOrigin({ 215, 120 });
	fin_game_over.setString("GAME OVER");
	fin_game_over.setPosition({ 380, 250 });
	fin_options.setFont(Assets::font);
	fin_options.setCharacterSize(75);
	fin_options.setFillColor(Color::Green);
	fin_options.setPosition({ 320, 250 });
	std::ostringstream str;
	str << "MENU" << std::endl << "EXIT";
	fin_options.setString(str.str());
	fin_cursor.setRadius(1.33f * BALL_R);
	fin_cursor.setOrigin({ 1.33f * BALL_R, 1.33f * BALL_R });
	fin_cursor.setTexture(&Assets::bomb_tex[14]);
	fin_cursor.setPosition({ 275, 370 });
	fin_option_switch.setBuffer(Assets::option);
	Level::score = 0;
	curLevel = new Level(LV);
	Ball::speed_mult = 1.0;
	losing_bg.setBuffer(Assets::losing);
}


Breakout::~Breakout()
{
	if (curLevel) delete curLevel;
}

void Breakout::sky_animate()
{
	sky.setTextureRect(IntRect(5 * sky_move_frame, 0, 800, 600));
	sky_move_frame = (sky_move_frame + 1) % 600;
}

int Breakout::run(RenderWindow& window)
{
	Clock clock;
	clock.restart();
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return EXIT;
			}
		}
		if (clock.getElapsedTime() > dt) { // appro 60 fps
			float dt = clock.restart().asSeconds();
			update_state(dt);
			// exit condition
			if (status == ENDING || status == END) if (losing_bg.getStatus() != Sound::Playing) losing_bg.play();
			if (status == END) {
				Vector2f pos = fin_cursor.getPosition();
				if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
					if (pos.y > 295.0f && pos.y <= 370.0f) {
						pos.y -= 75.0f;
						fin_option_switch.play();
					}
				if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
					if (pos.y >= 295.0f && pos.y < 370.0f) {
						pos.y += 75.0f;
						fin_option_switch.play();
					}
				fin_cursor.setPosition(pos);
				if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) {
					Assets::button_press.play();
					if (pos.y == 295.0f) {
						if (losing_bg.getStatus() == Sound::Playing) losing_bg.stop();
						return MENU; // menu
					}
					if (pos.y == 370.0f) {
						if (losing_bg.getStatus() == Sound::Playing) losing_bg.stop();
						return EXIT; // exit
					}
				}
			}
			render_frame(window);
			clock.restart();
		}
	}
	return EXIT;
}

void Breakout::update_state(float dt)
{
	if (curLevel->status == CLEAR) {
		delete curLevel;
		curLevel = new Level(++LV);
		player.status = START;
		Ball::speed_mult += 0.2f;
		bullet.status = UNLAUNCHED;
	}

	if ((curLevel->status == PREPARE || curLevel->status == NOT_CLEAR) && !player.isDead())
		if (curLevel->level_bg.getStatus() != Sound::Playing) curLevel->level_bg.play();
	curLevel->update_state(dt);
	if (status == RUNNING) {
		if (curLevel->status == NOT_CLEAR) player.update_state(dt);
		if (curLevel->status == NOT_CLEAR) bullet.update_state(dt, player, curLevel->brick_list);
		if (player.isDead()) {
			if (curLevel->level_bg.getStatus() == Sound::Playing) curLevel->level_bg.stop();
			status = ENDING;
		}
	}
}

void Breakout::render_frame(RenderWindow& window)
{
	// draw sky
	++rate;
	if (rate / SKY_RATE) {
		sky_animate();
		rate = 0;
	}
	window.clear(Color(150, 150, 150));
	window.draw(sky);

	curLevel->draw(window);

	// draw everything else
	if (status != END) {
		window.draw(rail);
		if (curLevel->status == NOT_CLEAR) bullet.drawBullet(window);
		player.draw(window);
		if (status != ENDING) bullet.drawExplosion(window);
	}
	else {
		window.draw(fin_game_over);
		window.draw(fin_options);
		window.draw(fin_cursor);
	}

	if (status == ENDING) { // render 2 series of explosions
		++exp_rate;
		if (exp_rate / EXP_RATE) {
			for (int i = 0; i < 8; ++i) explosions[i].setTexture(&Assets::explode_tex[expl_fr]);
			++expl_fr;
			if (expl_fr == 28) { // single explosion ends
				expl_fr = 0;
				for (int i = 0; i < 8; ++i) explosions[i].setTexture(&Assets::explode_tex[expl_fr]);
				if (expl_times < 1) if (expl_sound.getStatus() != SoundSource::Playing) expl_sound.play();
				++expl_times;
			}
			if (expl_times == 2) { // two explosions end
				status = END;
				expl_times = 0;
				game_over.play();
			}
			exp_rate = 0;
		}
		for (int i = 0; i < 8; ++i) window.draw(explosions[i]);
	}

	window.display();
}