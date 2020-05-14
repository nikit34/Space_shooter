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

	void initView();
	void initTextures();
	void initMapTextures();
	void initMap();
	void initUI();
	void initialize();
	
	void updateView();
	void update(const float& dt);
	void updateTimers(const float& dt);
	
	void mapUpdate();

	void draw();
	void drawMap();
	void drawUI();

private:
	// GameMapMaker
	RenderWindow* window;
	View mainView;
	bool fullscreen;
	float dtMultiplier;
	float keyTimeMax;
	float keyTime;

	// UI
	// Text
	Font font;

	// Map
	Map map;
	Stage stage;
};