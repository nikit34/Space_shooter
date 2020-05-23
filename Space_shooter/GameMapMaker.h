#pragma once
#include"Player.h"
#include"Enemy.h"
#include"Boss.h"
#include"Map.h"


class GameMapMaker {
public:
	GameMapMaker(RenderWindow* window);
	virtual ~GameMapMaker();

	// Accessors
	inline RenderWindow& getWindow() { return *this->window; }

	// Setters

	// Functions
	void toggleFullscreen();

	void newStage();
	void saveStage();
	void loadStage();
	void setBackground();
	void setEnemySpawner();

	void initView();
	void initTextures();
	void initMap();
	void initText();
	void initButtons();
	void initUI();
	void initialize();
	
	void updateMousePositions();
	void updateView(const float& dt);
	void updateControls();
	void updateAddRemoveTiles();
	void updateText();
	void updateButtons();
	void updateUI();
	void update(const float& dt);
	void updateTimers(const float& dt);
	void mapUpdate(const float& dt);

	void draw();
	void drawText();
	void drawMap();
	void drawUIView();
	void drawUIWindow();

private:
	// GameMapMaker
	RenderWindow* window;
	View mainView;
	float dtMultiplier;
	bool fullscreen;
	float keyTimeMax;
	float keyTime;
	int backgroundIndex;
	int backgroundWidth;
	int backgroundHeight;

	int toolSelect;

	// enemySpawner
	Vector2i enemyPosGrid;
	bool enemyRandomSpawnPos;
	int enemyMaxVelocity;
	int enemyType;
	int enemyLevelInterval;
	int nrOfEnemies;

	// Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosWorld;
	Vector2i mousePosGrid;

	// UI
	bool windowUI;

	int textureX;
	int textureY;
	RectangleShape selector;
	Sprite textureSelector;

	// Buttons
	dArr<WButton> buttons;

	// Text
	Font font;
	Text selectorText;
	Text enemySpawnerText;

	// Map
	std::string stageName;
	Stage *stage;
};