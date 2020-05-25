#pragma once
#include"Wingman.h"
#include"WButton.h"

static enum Mode { Survival = 0, Regular };

class MainMenu {
public:
	MainMenu(
		RenderWindow* window, 
		int mode
	);
	virtual ~MainMenu();

	// Init
	void initBackground();
	void initButtons();
	void initialize();

	// Accessors
	inline bool getExit()const { return this->exitProgram; }
	inline int getMode()const { return this->mode; }
	inline bool viewMainMenu()const { return this->view; }

	// Setters
	inline void setViewMainMenu(bool view) { this->view = view; }

	// Update
	void updateTimers(const float& dt);
	void updateBackground(Vector2f& mPos, const float& dt);
	void updateButtons(Vector2f& mPos);
	void update(Vector2f& mPos, const float& dt);

	// Draw
	void drawBackground(RenderTarget& target);
	void drawButtons(RenderTarget& target);
	void draw(RenderTarget& target);

	dArr<WButton> buttons;

	

private:
	RenderWindow* window;
	float dtMultiplier;
	float keyTimeMax;
	float keyTime;
	Font font;
	Vector2u windowBounds;

	bool exitProgram;
	bool view;

	bool constructor;
	int mode;
 
	enum buttons { CONSTRUCTOR_BTN = 0, NORMAL_MODE_BTN, SURVIVAL_MODE_BTN, EXIT_BTN };
};

