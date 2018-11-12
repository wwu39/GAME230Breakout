#include "Assets.h"
#include "Breakout.h"

Breakout::Breakout()
{
	rail.setSize({ 800, 28 });
	rail.setOrigin({ 400, 14 });
	rail.setTexture(&Assets::rail_tex);
	rail.setPosition(400, 564);
}


Breakout::~Breakout()
{
}

int Breakout::run(RenderWindow& window)
{
	Clock clock;
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
			render_frame(window);
			clock.restart();
		}
	}
	return EXIT;
}

void Breakout::update_state(float dt)
{
	player.move(dt);
}

void Breakout::render_frame(RenderWindow& window)
{
	window.clear(Color(0, 0, 255));
	window.draw(rail);
	player.draw(window);
	window.display();
}