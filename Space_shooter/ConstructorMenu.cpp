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
	this->constructor = false;
}

ConstructorMenu::~ConstructorMenu() {}


void ConstructorMenu::initBackground() {

}

void ConstructorMenu::initButtons() {
	this->buttons.add(WButton(
		GAME_BTN,
		this->font,
		"MAP MAKER",
		18,
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.25f),
		0
	));
	this->buttons.add(WButton(
		EXIT_BTN,
		this->font,
		"EXIT -->",
		18,
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.75f),
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

void ConstructorMenu::updateBackground(Vector2f& mPos, const float& dt) {

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
	this->updateBackground(mPos, dt);

	// Buttons update
	this->updateButtons(mPos);
}

void ConstructorMenu::drawBackground(RenderTarget& target) {

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