#include"MainMenu.h"


MainMenu::MainMenu(
	RenderWindow* window, 
	int mode
) {
	this->window = window;
	this->mode = mode;
	this->window->setFramerateLimit(200);
	this->windowBounds = this->window->getSize();
	this->dtMultiplier = 60.f;
	this->keyTimeMax = 20.f;
	this->keyTime = 0;

	this->initialize();

	this->exitProgram = false;
	this->view = true;
	this->game = true;
}

MainMenu::~MainMenu() {}


void MainMenu::initBackground() {
	this->background.loadFromFile("Textures/Backgrounds/bgMainMenu.png");
	this->spriteBackground.setTexture(this->background);
	this->spriteBackground.setScale(
		this->windowBounds.x / this->spriteBackground.getGlobalBounds().width * 1.5f,
		this->windowBounds.y / this->spriteBackground.getGlobalBounds().height * 1.5f);
	this->spriteBackground.setPosition(
		-this->spriteBackground.getGlobalBounds().width * 0.25f,
		-this->spriteBackground.getGlobalBounds().height * 0.25f);
}

void MainMenu::initButtons() {
	this->buttons.add(WButton(
		CONSTRUCTOR_BTN,
		this->font,
		"MAP MAKER",
		18,
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.1f),
		Vector2f(0.7f, 0.55f),
		0
	));
	this->buttons.add(WButton(
		PLAY_BTN,
		this->font,
		"PLAY",
		20,
		Vector2f(this->windowBounds.x * 0.25f, this->windowBounds.y * 0.85f),
		Vector2f(0.7f, 0.55f),
		0
	));
	this->buttons.add(WButton(
		NORMAL_MODE_BTN, 
		this->font, 
		"NORMAL", 
		18, 
		Vector2f(this->windowBounds.x * 0.75f - 200.f, this->windowBounds.y * 0.85f),
		Vector2f(0.6f, 0.5f),
		0
	));
	this->buttons.add(WButton(
		SURVIVAL_MODE_BTN, 
		this->font, 
		"SURVIVAL", 
		18, 
		Vector2f(this->windowBounds.x * 0.75f, this->windowBounds.y * 0.85f),
		Vector2f(0.6f, 0.5f),
		0
	));
	this->buttons.add(WButton(
		EXIT_BTN, 
		this->font, 
		"EXIT -->", 
		18, 
		Vector2f(this->windowBounds.x * 0.75f + 200.f, this->windowBounds.y * 0.85f),
		Vector2f(0.6f, 0.5f),
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

void MainMenu::updateBackground(Vector2f& mPos) {
	this->spriteBackground.setPosition(
		 - mPos.x / 2.5f - this->windowBounds.x / 10,
		 - mPos.y / 2.5f - this->windowBounds.y / 10);
}

void MainMenu::updateButtons(Vector2f &mPos) {
	for (size_t i = 0; i < this->buttons.size(); i++) {

		this->buttons[i].update(mPos);
		
		if (Mouse::isButtonPressed(Mouse::Left) && 
			this->keyTime >= this->keyTimeMax &&
			this->buttons[i].getBounds().contains(mPos)
		) {
			// Constructor
			if (this->buttons[i].getId() == buttons::CONSTRUCTOR_BTN) {
				this->game = false;
			}

			// Play
			if (this->buttons[i].getId() == buttons::PLAY_BTN) {
				this->view = false;
			}

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
			this->view = false;
		}
	}
}

void MainMenu::update(Vector2f& mPos, const float& dt) {
	// Timers update
	this->updateTimers(dt);

	// Background update
	this->updateBackground(mPos);
	
	// Buttons update
	this->updateButtons(mPos);
}

void MainMenu::drawBackground(RenderTarget& target) {
	target.draw(this->spriteBackground);
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