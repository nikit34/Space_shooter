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
	void Update(const float& dt);
	void DrawUI();
	void Draw();

private:
	RenderWindow* window;
	float dtMultiplier;

	// Text
	Font font;
	std::vector<Text> followPlayerTexts;
	std::vector<Text> staticPlayerTexts;
	Text enemyText;
	Text gameOverText;

	// Players
	std::vector<Player> players;
	int playersAlive;

	// Enemies
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimerMax;
	float enemySpawnTimer;

	// Textures
	std::vector<Texture> textures;
};
