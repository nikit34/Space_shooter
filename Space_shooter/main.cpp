#include"Game.h"


int main() {
	RenderWindow window(VideoMode(800, 600), "SpaceGame", Style::Default);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
	}
	return 0;
}