#include "MainMenu.h"


MainMenu::MainMenu(
	RenderWindow* window, 
	int mode
) {
	this->window = window;
	this->mode = mode;
	this->window->setFramerateLimit(200);
	this->windowBounds = this->window->getSize();
	this->dtMultiplier = 60.f;
	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;

	this->initialize();

	this->exitProgram = false;
	this->close = false;
}

MainMenu::~MainMenu() {}


void MainMenu::initBackground() {

}

void MainMenu::initButtons() {
	this->buttons.add(WButton(
		NORMAL_MODE_BTN, 
		this->font, 
		"Normal", 
		18, 
		Vector2f(this->windowBounds.x * 0.75f - 200.f, this->windowBounds.y * 0.75f),
		0
	));
	this->buttons.add(WButton(
		SURVIVAL_MODE_BTN, 
		this->font, 
		"Survival", 
		18, 
		Vector2f(this->windowBounds.x * 0.75f, this->windowBounds.y * 0.75f),
		0
	));
	this->buttons.add(WButton(
		EXIT_BTN, 
		this->font, 
		"Exit -->", 
		18, 
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.75f),
		0
	));
}

void MainMenu::initialize() {
	this->font.loadFromFile("Fonts/Metropolian-Display.ttf");

	// Init background
	this->initBackground();

	// Init buttons
	this->initButtons();
}

void MainMenu::updateTimers(const float& dt) {
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;
}

void MainMenu::updateBackground(Vector2f& mPos, const float& dt) {

}

void MainMenu::updateButtons(Vector2f &mPos) {
	for (size_t i = 0; i < this->buttons.size(); i++) {

		this->buttons[i].update(mPos);
		
		if (Mouse::isButtonPressed(Mouse::Left) && 
			this->keyTime >= this->keyTimeMax &&
			this->buttons[i].getBounds().contains(mPos)
		) {
			// Set normal mode
			if (this->buttons[i].getId() == buttons::NORMAL_MODE_BTN) {
				this->mode = Mode::Regular;
			}

			// Set survival mode
			if (this->buttons[i].getId() == buttons::SURVIVAL_MODE_BTN) {
				this->mode = Mode::Survival;
			}
			
			// Exit event
			if (this->buttons[i].getId() == buttons::EXIT_BTN) {
				this->exitProgram = true;
			}
			this->keyTime = 0.f;
			this->close = true;
		}
	}
}

void MainMenu::update(Vector2f& mPos, const float& dt) {
	// Timers update
	this->updateTimers(dt);

	// Background update
	this->updateBackground(mPos, dt);
	
	// Buttons update
	this->updateButtons(mPos);
}

void MainMenu::drawBackground(RenderTarget& target) {

}

void MainMenu::drawButtons(RenderTarget& target) {
	for (size_t i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].draw(target);
	}
}

void MainMenu::draw(RenderTarget& target) {
	// Draw background
	this->drawBackground(target);
	
	// Draw buttons
	this->drawButtons(target);
}