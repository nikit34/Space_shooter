#include "GameMapMaker.h"

enum textures { player = 0, laser01, missile01 };

GameMapMaker::GameMapMaker(RenderWindow* window) {
	this->window = window;
	this->window->setFramerateLimit(200);
	this->fullscreen = false;
	this->dtMultiplier = 60.f;

	this->stage = nullptr;

	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;

	this->initialize();
}

GameMapMaker::~GameMapMaker() {
	delete this->stage;
}



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
	this->stage = new Stage(10, 10);
}

void GameMapMaker::initUI() {
	this->selector.setSize(Vector2f(Wingman::gridSize, Wingman::gridSize));
	this->selector.setFillColor(Color::Transparent);
	this->selector.setOutlineColor(Color::Red);
	this->selector.setOutlineThickness(2.f);
}



void GameMapMaker::update(const float& dt) {
	// Timers update
	this->updateTimers(dt);

	// Mouse positions
	this->updateMousePositions();
	
	// Fullscreen
	this->toggleFullscreen();

	// Map
	this->mapUpdate();

	// Add tiles
	this->updateAddTiles();

	// UI update
	this->updateUI();

	// View
	this->updateView(dt);
}

void GameMapMaker::updateTimers(const float& dt) {
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;
}

void GameMapMaker::updateMousePositions() {
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosWorld = this->window->mapPixelToCoords(this->mousePosWindow);
	this->mousePosGrid.x = this->mousePosWorld.x / Wingman::gridSize;
	this->mousePosGrid.y = this->mousePosWorld.y / Wingman::gridSize;

	if (this->mousePosGrid.x < 0)
		this->mousePosGrid.x = 0;
	if (this->mousePosGrid.y < 0)
		this->mousePosGrid.y = 0;
	if (this->mousePosGrid.x >= this->stage->getSizeX())
		this->mousePosGrid.x = this->stage->getSizeX() - 1;
	if (this->mousePosGrid.y >= this->stage->getSizeY())
		this->mousePosGrid.y = this->stage->getSizeY() - 1;
}

void GameMapMaker::mapUpdate() {

}

void GameMapMaker::updateAddTiles() {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		this->stage->addTile(
			Tile(IntRect(0, 0, 50, 50),
				this->selector.getPosition(),
				false,
				false),
			this->mousePosGrid.x, 
			this->mousePosGrid.y
		);
	}
}

void GameMapMaker::updateUI() {
	this->selector.setPosition(
		this->mousePosGrid.x * Wingman::gridSize,
		this->mousePosGrid.y * Wingman::gridSize);
}

void GameMapMaker::updateView(const float &dt) {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->mainView.move(0.f, -10.f * dt * this->dtMultiplier);
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->mainView.move(0.f, 10.f * dt * this->dtMultiplier);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		this->mainView.move(-10.f * dt * this->dtMultiplier, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		this->mainView.move(10.f * dt * this->dtMultiplier, 0.f);
	}
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
	this->stage->draw(*this->window, this->mainView);
}

void GameMapMaker::drawUI() {
	this->window->draw(this->selector);
}


