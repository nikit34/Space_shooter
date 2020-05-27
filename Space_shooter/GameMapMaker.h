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
	inline bool getExit()const { return this->constructorMenu->getExit(); }
	inline bool getStatConstructor()const { return this->constructorMenu->getStatConstructor(); }

	// Setters
	void setMode();
	inline void setStatConstructor(bool constructor) { this->constructorMenu->setStatConstructor(constructor); }
	
	// Functions
	void newStage();
	void saveStage();
	void loadStage();
	void setBackground();
	void setEnemySpawner();

	void initView();
	void initMap();
	void initText();
	void initMenu();
	void initUI();
	void initialize();
	
	void update(const float& dt);
	void updateTimers(const float& dt);
	void toggleFullscreen(); 
	void updateMousePositions();
	void stopConstructor();
	void updateControls();
	void updateAddRemoveTiles();
	void updateMap(const float& dt);
	void updateText();
	void updateUI();
	void updateView(const float& dt);
	void updateConstructorMenu(const float& dt);

	void draw();
	void drawText();
	void drawMap();
	void drawUIWindow();
	void drawUIView();
	void drawConstructorMenu();

private:
	// Menu constructor
	ConstructorMenu* constructorMenu;

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

	// Tiles
	bool tileCollider;

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

	// Text
	Font font;
	Text selectorText;
	Text enemySpawnerText;

	// Map
	std::string stageName;
	Stage *stage;
};