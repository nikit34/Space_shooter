#pragma once

#include"Player.h"


class Game
{
public:
	Game(RenderWindow *window);
	virtual ~Game();

	//Accessors
	RenderWindow &getWindow() { return *this->window; }

	//Setters


	//Functions
	void Update();
	void Draw();

private:
	RenderWindow *window;

	Player *player;
	Texture playerTexture;
};

