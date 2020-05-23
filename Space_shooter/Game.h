#pragma once

#include"Player.h"
#include"Enemy.h"
#include"Boss.h"
#include"Map.h"

enum Mode { Survival = 0, Regular };

class Game {
public:
	Game(RenderWindow* window);
	virtual ~Game();

	// Accessors
	inline RenderWindow& getWindow() { return *this->window; }

	// Setters

	// Functions
	void initRT();
	void initView();
	void initTextures();
	void initMap();
	void initUI();
	void initialize();

	void updateView(const float& dt);
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
	void enemySpawnUpdate(const float& dt);
	void enemyBulletUpdate(const float& dt);
	void textTagsUpdate(const float& dt);
	void upgradesUpdate(const float& dt);
	void powerupsUpdate(const float& dt);
	void mapUpdate(const float& dt);
	void particlesUpdate(const float& dt);
	void pickupsUpdate(const float& dt);
	void setEndingScoreboard();
	void restartUpdate();

	void draw();
	void drawMap();
	void drawPlayer();
	void drawEnemies();
	void drawPickups();
	void drawUpgrades();
	void drawPowerups();
	void drawParticles();
	void drawTextTags();
	void drawUI();
	void updateUIPlayer(int index);
	void updateUIEnemy(int index);

private:
	// Game
	RenderWindow* window;
	View mainView;
	RenderTexture mainRenderTexture;
	Sprite mainRenderSprite;
	bool fullscreen;
	float dtMultiplier;
	bool paused;
	float keyTimeMax;
	float keyTime;
	int mode;

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
	RectangleShape playerShieldBar;
	RectangleShape playerPowerupBar;

	// Backgrounds
	RectangleShape playerStatsTextBack;

	// Texttags
	dArr<TextTag> textTags;

	// Map
	Stage *stage;
	int fromCol, toCol;
	int fromRow, toRow;

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

	// Powerups
	dArr<Powerup>powerups;

	// Particles
	dArr<Particle> particles;

	// Pickup textures
	unsigned nrOfPickups;
	dArr<Texture> pickupTextures;

	// Enemy textures
	dArr<Texture> enemyTextures;
	dArr<Texture> enemyBulletTextures;
};
