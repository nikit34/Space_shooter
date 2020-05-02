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
	void ToggleFullscreen();
	void PauseGame();
	void InitTextures();
	void InitUI();
	void InitMap();
	void RestartUpdate();
	void setEndingScoreboard();
	void UpdateTimers(const float& dt);
	void UpdateTimersUnpaused(const float& dt);
	void UpdateScore();
	void UpdateDifficulty();
	void UpdateUIPlayer(int index);
	void UpdateUIEnemy(int index);
	void UpdateWhilePaused(const float& dt);
	void PlayerUpdate(const float& dt);
	void PlayerBulletUpdate(const float& dt, const int i);
	void EnemyUpdate(const float& dt);
	void EnemyBulletUpdate(const float& dt);
	void TextTagsUpdate(const float& dt);
	void PickupsUpdate(const float& dt);
	void UpgradesUpdate(const float& dt);
	void Update(const float& dt);
	void DrawUI();
	void Draw();
	void DrawPlayer();
	void DrawEnemies();
	void DrawMap();
	void DrawPickups();
	void DrawUpgrades();

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
