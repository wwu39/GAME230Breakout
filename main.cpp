#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "Assets.h"
#include "Breakout.h"

enum MENU_STATUS { NONE = 0, LOADING, EXIT_FROM_GAME };

using namespace sf;

int main()
{
	Assets::loadAssets(); // load all files

	RenderWindow window;
	RectangleShape background;
	RectangleShape loadingsc;
	Text press_any_key;
	Text loading_text;
	MENU_STATUS status = MENU_STATUS::NONE;
	Sound title;
	Sound menu_bg;
	int rate = RATE;
	int rate2 = 0;
	int flashRate = 0;
	int loadingRate = 0;
	int loadingTextIdx = 0;
	std::string loadingStr[] = { "LOADING", "LOADING.", "LOADING.." , "LOADING..." };
	int rc = 0; // return value

	Breakout * game = nullptr; // the game

	// setup background
	background.setSize({ 800, 600 });
	background.setTexture(&Assets::menu_bgtex);
	loadingsc.setSize({ 800, 600 });
	loadingsc.setTexture(&Assets::menu_ldtex);

	// setup texts
	press_any_key.setFont(Assets::font);
	press_any_key.setCharacterSize(50);
	press_any_key.setFillColor(Color::Green);
	press_any_key.setPosition(100, 450);
	press_any_key.setString("Press Space to Continue...");

	loading_text.setFont(Assets::font);
	loading_text.setCharacterSize(100);
	loading_text.setFillColor(Color::Green);
	loading_text.setPosition(200, 200);
	loading_text.setString(loadingStr[0]);

	// title sound
	title.setBuffer(Assets::title);
	menu_bg.setBuffer(Assets::menu_bg);

	// setup window
	window.create(VideoMode(800, 600), GAMETILE);
	title.play();

	Clock clock;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return 0;
			}
		}

		if (clock.getElapsedTime() > dt) { // appro 60 fps

			// update state
			if (menu_bg.getStatus() != Sound::Playing) menu_bg.play();
			if (status == MENU_STATUS::NONE) {
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					if (menu_bg.getStatus() == Sound::Playing) menu_bg.stop();
					Assets::button_press.play();
					status = MENU_STATUS::LOADING;
				}
			}

			if (status == MENU_STATUS::EXIT_FROM_GAME) {
				++rate2;
				if (rate2 / (RATE * 5)) {
					status = MENU_STATUS::NONE;
					rate2 = 0;
				}
			}

			if (status == MENU_STATUS::LOADING) {
				if (game == nullptr) game = new Breakout();
				++loadingRate;
				if (loadingRate / (RATE * 5)) {
					++loadingTextIdx;
					if (loadingTextIdx == 4) {
						loadingTextIdx = 0;
						if (menu_bg.getStatus() == Sound::Playing) menu_bg.stop();
						rc = game->run(window);
						delete game;
						game = nullptr;
						if (rc == EXIT) return rc;
						if (rc == MENU) {
							title.play();
							status = MENU_STATUS::EXIT_FROM_GAME;
						}
					}
					loading_text.setString(loadingStr[loadingTextIdx]);
					loadingRate = 0;
				}
			}

			// render frame
			window.clear(Color(0, 0, 255));

			if (status != MENU_STATUS::LOADING) {
				window.draw(background);

				++flashRate;
				if (flashRate / (RATE * 2)) flashRate = 0;
				else window.draw(press_any_key);
			}
			else {
				window.draw(loadingsc);
				window.draw(loading_text);
			}

			window.display();

			clock.restart();
		}
	}
}