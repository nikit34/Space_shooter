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
	void UIUpdate();
	void CombatUpdate();
	void Update();
	void Draw();

private:
	RenderWindow *window;
	Font font;
	std::vector<Player> players;
	Texture playerTexture;
	Texture bulletTexture;
};

