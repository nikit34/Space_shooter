#include "ConstructorMenu.h"


ConstructorMenu::ConstructorMenu(RenderWindow* window) {
	this->window = window;
	this->window->setFramerateLimit(200);
	this->windowBounds = this->window->getSize();
	this->dtMultiplier = 60.f;
	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;

	this->initialize();

	this->exitProgram = false;
	this->view = true;
	
	this->followPressKey = -1;
	
	this->constructor = false;

}

ConstructorMenu::~ConstructorMenu() {}


void ConstructorMenu::initBackground() {
	this->background.loadFromFile("Textures/Backgrounds/bgConstructorMenu.png");
	this->spriteBackground.setTexture(this->background);
	this->spriteBackground.setScale(
		this->windowBounds.x / this->spriteBackground.getGlobalBounds().width * 1.5f,
		this->windowBounds.y / this->spriteBackground.getGlobalBounds().height * 1.5f);
	this->spriteBackground.setPosition(
		-this->spriteBackground.getGlobalBounds().width * 0.25f,
		-this->spriteBackground.getGlobalBounds().height * 0.25f);
}

void ConstructorMenu::initButtons() {
	this->buttons.add(WButton(
		GAME_BTN,
		this->font,
		"GAME",
		18,
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.1f),
		Vector2f(0.6f, 0.5f),
		0
	));
	this->buttons.add(WButton(
		BACKGROUND_TILES_BTN,
		this->font,
		"Back tiles",
		18,
		Vector2f(this->windowBounds.x * 0.25f - 300.f, this->windowBounds.y * 0.85f),
		Vector2f(0.8f, 0.6f),
		0
	));
	this->buttons.add(WButton(
		SELECT_BACKGROUNDS_BTN,
		this->font,
		"Backgrounds",
		18,
		Vector2f(this->windowBounds.x * 0.25f - 300.f, this->windowBounds.y * 0.85f - 100.f),
		Vector2f(0.8f, 0.6f),
		0
	));
	this->buttons.add(WButton(
		TILES_BTN,
		this->font,
		"Reg. tiles",
		18,
		Vector2f(this->windowBounds.x * 0.25f, this->windowBounds.y * 0.85f),
		Vector2f(0.8f, 0.6f),
		0
	));
	this->buttons.add(WButton(
		TOGGLE_TILE_COLLIDE_BTN,
		this->font,
		"Collide tiles",
		18,
		Vector2f(this->windowBounds.x * 0.25f, this->windowBounds.y * 0.85f - 100.f),
		Vector2f(0.8f, 0.6f),
		0
	));
	this->buttons.add(WButton(
		ENEMIES_BTN,
		this->font,
		"Enemies",
		18,
		Vector2f(this->windowBounds.x * 0.25f + 300.f, this->windowBounds.y * 0.85f),
		Vector2f(0.8f, 0.6f),
		0
	));
	this->buttons.add(WButton(
		FEATURE_ENEMIES_BTN,
		this->font,
		"Feature enemy",
		18,
		Vector2f(this->windowBounds.x * 0.25f + 300.f, this->windowBounds.y * 0.85f - 100.f),
		Vector2f(0.8f, 0.6f),
		0
	));
	this->buttons.add(WButton(
		NEW_STAGE_BTN,
		this->font,
		"NEW STAGE",
		18,
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.85f - 300.f),
		Vector2f(0.6f, 0.5f),
		0
	));
	this->buttons.add(WButton(
		SAVE_BTN,
		this->font,
		"SAVE",
		18,
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.85f - 100.f),
		Vector2f(0.6f, 0.5f),
		0
	));
	this->buttons.add(WButton(
		LOAD_BTN,
		this->font,
		"LOAD",
		18,
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.85f - 200.f),
		Vector2f(0.6f, 0.5f),
		0
	));
	this->buttons.add(WButton(
		EXIT_BTN,
		this->font,
		"EXIT -->",
		18,
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.85f),
		Vector2f(0.6f, 0.6f),
		0
	));
}

void ConstructorMenu::initialize() {
	this->font.loadFromFile("Fonts/Metropolian-Display.ttf");

	// Init background
	this->initBackground();

	// Init buttons
	this->initButtons();
}

void ConstructorMenu::updateTimers(const float& dt) {
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;
}

void ConstructorMenu::updateBackground(Vector2f& mPos) {
	this->spriteBackground.setPosition(
		-mPos.x / 2.5f - this->windowBounds.x / 10,
		-mPos.y / 2.5f - this->windowBounds.y / 10);
}

void ConstructorMenu::updateButtons(Vector2f& mPos) {
	for (size_t i = 0; i < this->buttons.size(); i++) {

		this->buttons[i].update(mPos);

		if (Mouse::isButtonPressed(Mouse::Left) &&
			this->keyTime >= this->keyTimeMax &&
			this->buttons[i].getBounds().contains(mPos)
			) {
			// Constructor
			if (this->buttons[i].getId() == buttons::GAME_BTN) {
				this->constructor = false;
			}
			// Set back tiles
			if (this->buttons[i].getId() == buttons::BACKGROUND_TILES_BTN) {
				this->followPressKey = buttons::BACKGROUND_TILES_BTN;
			}
			// Select backgrounds
			if (this->buttons[i].getId() == buttons::SELECT_BACKGROUNDS_BTN) {
				this->followPressKey = buttons::SELECT_BACKGROUNDS_BTN;
			}
			// Set tiles
			if (this->buttons[i].getId() == buttons::TILES_BTN) {
				this->followPressKey = buttons::TILES_BTN;
			}
			// Toggle collide tiles
			if (this->buttons[i].getId() == buttons::TOGGLE_TILE_COLLIDE_BTN) {
				this->followPressKey = buttons::TOGGLE_TILE_COLLIDE_BTN;
			}
			// Set enemies
			if (this->buttons[i].getId() == buttons::ENEMIES_BTN) {
				this->followPressKey = buttons::ENEMIES_BTN;
			}
			// Set feature enemies
			if (this->buttons[i].getId() == buttons::FEATURE_ENEMIES_BTN) {
				this->followPressKey = buttons::FEATURE_ENEMIES_BTN;
			}
			// New stage
			if (this->buttons[i].getId() == buttons::NEW_STAGE_BTN) {
				this->followPressKey = buttons::NEW_STAGE_BTN;
			}
			// Save
			if (this->buttons[i].getId() == buttons::SAVE_BTN) {
				this->followPressKey = buttons::SAVE_BTN;
			}
			// Load
			if (this->buttons[i].getId() == buttons::LOAD_BTN) {
				this->followPressKey = buttons::LOAD_BTN;
			}
			// Exit event
			if (this->buttons[i].getId() == buttons::EXIT_BTN) {
				this->exitProgram = true;
			}
			this->keyTime = 0.f;
			this->view = false;
		}
	}
}

void ConstructorMenu::update(Vector2f& mPos, const float& dt) {
	// Timers update
	this->updateTimers(dt);

	// Background update
	this->updateBackground(mPos);

	// Buttons update
	this->updateButtons(mPos);
}

void ConstructorMenu::drawBackground(RenderTarget& target) {
	target.draw(this->spriteBackground);
}

void ConstructorMenu::drawButtons(RenderTarget& target) {
	for (size_t i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].draw(target);
	}
}

void ConstructorMenu::draw(RenderTarget& target) {
	// Draw background
	this->drawBackground(target);

	// Draw buttons
	this->drawButtons(target);
}