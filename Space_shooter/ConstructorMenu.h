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

	enum buttons { GAME_BTN = 0, EXIT_BTN };
};
