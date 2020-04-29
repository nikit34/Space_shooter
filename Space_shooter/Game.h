#pragma once

#include"Enemy.h"
#include"Player.h"


class Game {
public:
	Game(RenderWindow* window);
	virtual ~Game();

	// Accessors
	inline RenderWindow& getWindow() { return *this->window; }

	// Setters

	// Functions
	void toggleFullscreen();
	void InitTextures();
	void InitUI();
	void UpdateUIPlayer(int index);
	void UpdateUIEnemy(int index);
	void Update(const float& dt);
	void DrawUI();
	void Draw();

private:
	// Game
	RenderWindow* window;
	float dtMultiplier;
	bool paused;
	float keyTime;
	float keyTimeMax;
	bool fullscreen;
	
	// Score
	unsigned score;
	unsigned scoreMultiplier;
	Clock scoreTimer;
	int scoreTime;
	float multiplierTimer;
	float multiplierTimerMax;
	int multiplierAdder;
	int multiplierAdderMax;
	double bestScoreSecond;
	float difficultyTimer;
	int difficulty;

	// UI
	// Text
	Font font;
	Text followPlayerText;
	Text staticPlayerText;
	Text enemyText;
	Text gameOverText;
	Text scoreText;
	Text controlsText;

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
	float enemySpawnTimer;
	float enemySpawnTimerMax;

	// Pickup
	dArr<Pickup> pickups;

	// Upgrades
	dArr<Upgrade> upgrades;

	// Textures
	std::vector<Texture> textures;
	dArr<Texture> playerMainGunTextures;
	dArr<Texture> enemyTextures;
	dArr<Texture> enemyBulletTextures;
	dArr<Texture> lWingTextures;
	dArr<Texture> rWingTextures;
	dArr<Texture> cPitTextures;
	dArr<Texture> areaTextures;
	dArr<Texture> pickupTextures;
	dArr<Texture> upgradeTextures;
};
