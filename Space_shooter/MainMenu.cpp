#include "MainMenu.h"


MainMenu::MainMenu() {

}

MainMenu::~MainMenu() {}


void MainMenu::initBackground() {

}

void MainMenu::initButtons() {
	this->buttons.add(WButton(
		NORMAL_MODE_BTN, 
		this->font, 
		"Normal", 
		12, 
		Vector2f(this->windowBounds.x / 2 - 200.f, this->windowBounds.y / 2), 
		0
	));
	this->buttons.add(WButton(
		SURVIVAL_MODE_BTN, 
		this->font, 
		"Survival", 
		12, 
		Vector2f(this->windowBounds.x / 2, this->windowBounds.y / 2), 
		0
	));
	this->buttons.add(WButton(
		EXIT_BTN, 
		this->font, 
		"Exit to windows", 
		12, 
		Vector2f(this->windowBounds.x / 2 + 200.f, this->windowBounds.y / 2), 
		0
	));
}

void MainMenu::initialize(Vector2u windowBounds) {
	this->font.loadFromFile("Fonts/Metropolian-Display.ttf");
	this->windowBounds = windowBounds;
	this->initBackground();
	this->initButtons();
}

void MainMenu::updateBackground(Vector2f& mPos, const float& dt) {

}

void MainMenu::updateButtons(Vector2f &mPos, const float& dt) {
	for (size_t i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].update(mPos);
	}
}

void MainMenu::update(Vector2f& mPos, const float& dt) {
	this->updateBackground(mPos, dt);
	this->updateButtons(mPos, dt);
}

void MainMenu::drawBackground(RenderTarget& target) {

}

void MainMenu::drawButtons(RenderTarget& target) {
	for (size_t i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].draw(target);
	}
}

void MainMenu::draw(RenderTarget& target) {
	this->drawBackground(target);
	this->drawButtons(target);
}