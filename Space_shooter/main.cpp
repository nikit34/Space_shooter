#include"Game.h"
#include"GameMapMaker.h"

// DEBUG - TODO: COMMENT!!!
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//
//#ifdef _DEBUG
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#else
//#define DBG_NEW new
//#endif
// !!!!!!!!!!!!!!!!!!!!!!!!


bool MAPMAKER = false;

int main() {
	srand(time(NULL));

	RenderWindow window(VideoMode(1920, 1080), "SpaceGame", Style::Default);

	Clock clock;
	float dt = 0.f;

	Game game(&window);
	GameMapMaker gameMapMaker(&window);

	// Game loop
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		dt = clock.restart().asSeconds();

		if (game.getStatConstructor()) {
			gameMapMaker.update(dt);
			gameMapMaker.draw();
		}
		else {
			game.update(dt);
			game.draw();
		}

		if (game.getExit()) {
			// DEBUG - TODO: COMMENT!!!
			// _CrtDumpMemoryLeaks();
			///////////////////////////
			window.close();
		}
	}
	return 0;
}