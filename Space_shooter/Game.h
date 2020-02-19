#pragma once

#include "Enemy.h"
#include "Player.h"

class Game {
public:
	Game(RenderWindow* window);
	virtual ~Game();

	// Accessors
	RenderWindow& getWindow() { return *this->window; }

	// Setters

	// Functions
	void InitUI();
	void UpdateUI();
	void Update();
	void DrawUI();
	void Draw();

private:
	RenderWindow* window;

	// Text
	Font font;
	std::vector<Text> followPlayerTexts;
	std::vector<Text> staticPlayerTexts;
	Text enemyText;

	// Players
	std::vector<Player> players;

	// Enemies
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	int enemySpawnTimerMax;
	int enemySpawnTimer;

	// Textures
	std::vector<Texture> textures;
};
