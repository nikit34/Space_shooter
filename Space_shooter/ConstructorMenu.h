#pragma once
#include"Wingman.h"
#include"WButton.h"


class ConstructorMenu {
public:
	ConstructorMenu(
		RenderWindow* window
	);
	virtual ~ConstructorMenu();

	// Init
	void initBackground();
	void initButtons();
	void initialize();

	// Accessors
	inline bool getExit()const { return this->exitProgram; }
	inline bool viewConstructorMenu()const { return this->view; }
	inline bool getStatConstructor()const { return this->constructor; }
	inline int getFollowKeyCode()const { return this->followPressKey; }

	// Setters
	inline void setViewConstructorMenu(bool view) { this->view = view; }
	inline void setStatConstructor(bool constructor) { this->constructor = constructor; }
	inline void setKeyCode(int keyCode) { this->followPressKey = keyCode; }

	// Update
	void updateTimers(const float& dt);
	void updateBackground(Vector2f& mPos);
	void updateButtons(Vector2f& mPos);
	void update(Vector2f& mPos, const float& dt);

	// Draw
	void drawBackground(RenderTarget& target);
	void drawButtons(RenderTarget& target);
	void draw(RenderTarget& target);

	dArr<WButton> buttons;

	enum buttons { 
		GAME_BTN = 0,  
		BACKGROUND_TILES_BTN,
		SELECT_BACKGROUNDS_BTN,
		TILES_BTN, 
		TOGGLE_TILE_COLLIDE_BTN,
		ENEMIES_BTN, 
		FEATURE_ENEMIES_BTN,
		NEW_STAGE_BTN,
		SAVE_BTN,
		LOAD_BTN,
		EXIT_BTN 
	};

private:
	RenderWindow* window;
	Vector2u windowBounds;
	float dtMultiplier;
	float keyTimeMax;
	float keyTime;

	Font font;
	Texture background;
	Sprite spriteBackground;

	bool exitProgram;
	bool view;

	int followPressKey;

	bool constructor;
};
