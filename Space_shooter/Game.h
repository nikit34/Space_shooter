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
	void InitTextures();
	void InitUI();
	void UpdateUIPlayer(int index);
	void UpdateUIEnemy(int index);
	void Update(const float& dt);
	void DrawUI();
	void Draw();

private:
	RenderWindow* window;
	float dtMultiplier;

	// Text
	Font font;
	Text followPlayerText;
	Text staticPlayerText;
	Text enemyText;
	Text gameOverText;

	// Bars
	RectangleShape playerExpBar;

	// TextTags
	dArr<TextTag> textTags;

	// Players
	dArr<Player> players;
	int playersAlive;

	// Enemies
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimerMax;
	float enemySpawnTimer;

	// Textures
	std::vector<Texture> textures;
	dArr<Texture> lWingTextures;
	dArr<Texture> rWingTextures;
	dArr<Texture> cPitTextures;
	dArr<Texture> areaTextures;
};
