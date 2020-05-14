#include "GameMapMaker.h"

enum textures { player = 0, laser01, missile01 };

GameMapMaker::GameMapMaker(RenderWindow* window) {
	this->window = window;
	this->window->setFramerateLimit(200);
	this->fullscreen = false;
	this->dtMultiplier = 60.f;

	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;

	this->initialize();
}

GameMapMaker::~GameMapMaker() {}



void GameMapMaker::toggleFullscreen() {
	if (Keyboard::isKeyPressed(Keyboard::F11) && this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;

		if (fullscreen) {
			this->fullscreen = false;
			this->window->close();
			this->window->create(sf::VideoMode(1920, 1080), "SpaceGame", Style::Default);
		}
		else {
			this->fullscreen = true;
			this->window->close();
			this->window->create(sf::VideoMode(1920, 1080), "SpaceGame", Style::Fullscreen);
		}
	}
}



void GameMapMaker::initialize() {
	// Init view
	this->initView();

	// Init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	// Init textures
	this->initTextures();

	// Init map
	this->initMap();

	// Init UI
	this->initUI();
}

void GameMapMaker::initView() {
	this->mainView.setSize(Vector2f(this->window->getSize()));
	this->mainView.setCenter(Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2));
}

void GameMapMaker::initTextures() {
	Texture temp;

	// Map
	this->initMapTextures();
}

void GameMapMaker::initMapTextures() {
	Tile::tileTextures.loadFromFile("Textures/Map/textureSheet.png");
}

void GameMapMaker::initMap() {

}

void GameMapMaker::initUI() {

}



void GameMapMaker::update(const float& dt) {
	// Timers update
	this->updateTimers(dt);

	// Fullscreen
	this->toggleFullscreen();

	// Map
	this->mapUpdate();

	// View
	this->updateView();
}

void GameMapMaker::updateTimers(const float& dt) {
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;
}

void GameMapMaker::mapUpdate() {

}

void GameMapMaker::updateView() {
	// this->mainView.setCenter(this->players[0].getPosition());
}



void GameMapMaker::draw() {
	// Clear
	this->window->clear();

	// Set view;
	this->window->setView(this->mainView);

	// Draw map
	this->drawMap();

	// Set view;
	this->window->setView(this->window->getDefaultView());

	// Draw UI
	this->drawUI();

	// Finish draw
	this->window->display();
}

void GameMapMaker::drawMap() {
	stage.draw(*this->window, this->mainView);
}

void GameMapMaker::drawUI() {

}


