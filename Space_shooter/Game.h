#pragma once

#include"Enemy.h"
#include"Player.h"
#include"Boss.h"

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
	void InitMap();
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

	// Map
	dArr<RectangleShape> walls;

	// Players
	dArr<Player> players;
	int playersAlive;

	// Enemies
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;

	// Bosses
	bool bossEncounter;
	dArr<Boss> bosses;

	// Pickup
	dArr<Pickup> pickups;

	// Upgrades
	dArr<Upgrade> upgrades;

	// Player textures
	std::vector<Texture> textures;
	dArr<Texture> playerMainGunTextures;
	dArr<Texture> lWingTextures;
	dArr<Texture> rWingTextures;
	dArr<Texture> cPitTextures;
	dArr<Texture> areaTextures;

	// Pickup/Update textures
	unsigned nrOfPickups;
	dArr<Texture> pickupTextures;
	unsigned nrOfUpgrades;
	dArr<Texture> upgradeTextures;

	// Enemy textures
	dArr<Texture> enemyTextures;
	dArr<Texture> enemyBulletTextures;

	// Boss textures
	dArr<Texture> bossBodyTextures;
	dArr<Texture> bossGunTextures;
	dArr<Texture> bossBulletTextures;
};
