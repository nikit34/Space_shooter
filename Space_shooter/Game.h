#pragma once

#include"Player.h"
#include"Enemy.h"
#include"Boss.h"
#include"Map.h"

class Game {
public:
	Game(RenderWindow* window);
	virtual ~Game();

	// Accessors
	inline RenderWindow& getWindow() { return *this->window; }

	// Setters

	// Functions
	void initTextures();
	void initPlayerTextures();
	void initMapTextures();
	void initMap();
	void initUI();
	void initialize();

	void update(const float& dt);
	void updateTimers(const float& dt);
	void toggleFullscreen();
	void pauseGame();
	void updateWhilePaused(const float& dt);
	void updateTimersUnpaused(const float& dt);
	void updateDifficulty();
	void updateScore();
	void playerUpdate(const float& dt);
	void playerBulletUpdate(const float& dt, const int i);
	void enemyUpdate(const float& dt);
	void enemyBulletUpdate(const float& dt);
	void textTagsUpdate(const float& dt);
	void upgradesUpdate(const float& dt);
	void mapUpdate();
	void pickupsUpdate(const float& dt);
	void setEndingScoreboard();
	void restartUpdate();

	void draw();
	void updateUIPlayer(int index);
	void updateUIEnemy(int index);
	void drawMap();
	void drawPlayer();
	void drawEnemies();
	void drawPickups();
	void drawUpgrades();
	void drawUI();

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
	Map map;
	Stage stage;

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
	dArr<Texture> playerBodyTextures;
	dArr<Texture> playerBulletTextures;
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
