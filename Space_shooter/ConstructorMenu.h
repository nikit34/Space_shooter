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

	// Setters
	inline void setViewConstructorMenu(bool view) { this->view = view; }
	inline void setStatConstructor(bool constructor) { this->constructor = constructor; }

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

	bool constructor;

	enum buttons { GAME_BTN = 0, SAVE_BTN, BACKGROUNDS_BTN, TILES_BTN, ENEMIES_BTN, EXIT_BTN };
};
