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

	void initView();
	void initTextures();
	void initMapTextures();
	void initMap();
	void initUI();
	void initialize();
	
	void updateMousePositions();
	void updateView(const float& dt);
	void updateControls();
	void updateAddRemoveTiles();
	void updateUI();
	void update(const float& dt);
	void updateTimers(const float& dt);
	void mapUpdate(const float& dt);

	void draw();
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
	bool backgroundTile;

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

	// Map
	std::string stageName;
	Stage *stage;
};