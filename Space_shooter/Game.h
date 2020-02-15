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
	void InitUI();
	void UpdateUI();
	void Update();
	void Draw();

private:
	RenderWindow *window;

	//Text
	Font font;
	std::vector<Text>followPlayerTexts;
	std::vector<Text>staticPlayerTexts;

	//Players
	std::vector<Player> players;
	
	//Textures
	Texture playerTexture;
	Texture bulletTexture;
};

