#pragma once

#include"Player.h"
#include"Enemy.h"
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
	void pauseGame();
	void initTextures();
	void initUI();
	void initMap();
	void restartUpdate();
	void setEndingScoreboard();
	void updateTimers(const float& dt);
	void updateTimersUnpaused(const float& dt);
	void updateScore();
	void updateDifficulty();
	void updateUIPlayer(int index);
	void updateUIEnemy(int index);
	void updateWhilePaused(const float& dt);
	void playerUpdate(const float& dt);
	void playerBulletUpdate(const float& dt, const int i);
	void enemyUpdate(const float& dt);
	void enemyBulletUpdate(const float& dt);
	void textTagsUpdate(const float& dt);
	void pickupsUpdate(const float& dt);
	void upgradesUpdate(const float& dt);
	void update(const float& dt);
	void drawUI();
	void draw();
	void drawPlayer();
	void drawEnemies();
	void drawMap();
	void drawPickups();
	void drawUpgrades();

private:
	// Game
	RenderWindow* window;
	bool fullscreen;
	float dtMultiplier;
	bool paused;
	float keyTimeMax;
	float keyTime;

	// Score
	unsigned scoreMultiplier;
	unsigned score;
	Clock scoreTimer;
	int scoreTime;
	int multiplierAdderMax;
	int multiplierAdder;
	float multiplierTimerMax;
	float multiplierTimer;
	double bestScoreSecond;
	int difficulty;
	float difficultyTimer;

	// UI
	// Text
	Font font;
	Text followPlayerText;
	Text staticPlayerText;
	Text playerStatsText;
	Text enemyText;
	Text gameOverText;
	Text scoreText;
	Text controlsText;

	// Bars
	RectangleShape playerExpBar;

	// Backgrounds
	RectangleShape playerStatsTextBack;

	// Texttags
	dArr<TextTag> textTags;

	// Map
	dArr<RectangleShape> walls;

	// Players
	dArr<Player> players;
	int playersAlive;

	// Enemies
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimerMax;
	float enemySpawnTimer;

	// Bosses
	bool bossEncounter;
	dArr<Boss> bosses;

	// Pickups
	dArr<Pickup> pickups;

	// Upgrades
	dArr<Upgrade> upgrades;

	// Player textures
	std::vector<Texture> textures;
	dArr<Texture> playerMainGunTextures;
	dArr<Texture> lWingTextures;
	dArr<Texture> rWingTextures;
	dArr<Texture> cPitTextures;
	dArr<Texture> auraTextures;

	// Pickup textures
	unsigned nrOfPickups;
	dArr<Texture> pickupTextures;

	// Upgrade textures
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
