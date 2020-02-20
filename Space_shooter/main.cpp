#include "Game.h"

int main() {
	RenderWindow window(VideoMode(1920, 1080), "SpaceGame", Style::Default);

	Game game(&window);

	Clock clock;
	float dt = 0.f;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		dt = clock.restart().asSeconds();
		game.Update(dt);
		game.Draw();
	}
	return 0;
}