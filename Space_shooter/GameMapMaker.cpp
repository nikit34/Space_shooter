#include "GameMapMaker.h"

enum textures { player = 0, laser01, missile01 };

GameMapMaker::GameMapMaker(RenderWindow* window) {
	this->window = window;
	this->window->setFramerateLimit(200);
	this->fullscreen = false;
	this->dtMultiplier = 60.f;
	this->toolSelect = Stage::tileType::regularTile;
	this->backgroundIndex = 0;
	this->backgroundWidth = Wingman::backgroundSize;
	this->backgroundHeight = Wingman::backgroundSize;
	this->stage = nullptr;

	// enemySpawner
	this->enemyRandomSpawnPos = false;
	enemyType = 0;
	enemyLevelInterval = 0;
	nrOfEnemies = 0;

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

void GameMapMaker::newStage() {
	unsigned mapSizeX = 0;
	unsigned mapSizeY = 0;
	std::cout << "New Map\n";
	std::cout << "Map Name: ";
	std::getline(std::cin, this->stageName);
	this->stageName.append(".wmap");

	std::cout << "\nSize X: ";
	std::cin >> mapSizeX;
	while (std::cin.fail() || mapSizeX <= 0) {
		std::cout << "\nFaulty input!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Size X: ";
		std::cin >> mapSizeX;
	}
	std::cout << "\nSize Y: ";
	std::cin >> mapSizeY;
	while (std::cin.fail() || mapSizeY <= 0) {
		std::cout << "\nFaulty input!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Size Y: ";
		std::cin >> mapSizeY;
	}
	std::cin.ignore(100, '\n');
	std::cout << '\n';

	delete this->stage;
	this->stage = new Stage(mapSizeX, mapSizeY);
	std::cout << "Stage " << this->stageName << " created\n";
}

void GameMapMaker::saveStage() {
	std::cout << "Save Stage\n";
	std::ifstream in;
	int choice = 0;
	in.open(this->stageName);
	if (in.is_open()) {
		std::cout << "File " << this->stageName << " already exists! Overwrite? (NO 0 / YES 1)\n";
		std::cout << "Choice: ";
		std::cin >> choice;
		while (std::cin.fail() || choice > 1) {
			std::cout << "\nFaulty input!\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Choice NO 0 / YES 1: ";
			std::cin >> choice;
		}
		std::cin.ignore(100, '\n');
		std::cout << '\n';
		if (choice == 0) {
			std::cout << "\nDid not overwrite\n";
		}
		else {
			this->stage->saveStage(this->stageName);
			std::cout << "\nStage " << this->stageName << " overwrite and save\n";
		}
	}
	else {
		this->stage->saveStage(this->stageName);
		std::cout << "\nStage " << this->stageName << " saved\n";
	}
}

void GameMapMaker::loadStage() {
	std::cout << "Load Stage\n";
	std::string fileName = "";
	std::cout << "File name: ";
	std::getline(std::cin, fileName);
	fileName.append(".wmap");
	if (this->stage->loadStage(fileName, this->mainView)) {
		this->stageName = fileName;
		std::cout << "\n" << fileName << " loaded\n";
	}
	else {
		std::cout << "\n" << "Could not load " << fileName << "\n";
	}
}

void GameMapMaker::setBackground() {
	int choice = 0;
	std::cout << "\nBackground select index (0 / " << Stage::nrOfTextures << "): ";
	std::cin >> choice;
	while (std::cin.fail() || choice >= Stage::nrOfTextures || choice < 0) {
		std::cout << "\nFaulty input!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "\nBackground select index (0 / " << Stage::nrOfTextures << "): ";
		std::cin >> choice;
	}
	this->backgroundIndex = choice;

	std::cout << "\nBackground size X: ";
	std::cin >> choice;
	while (std::cin.fail() || choice < Wingman::backgroundSize) {
		std::cout << "\nFaulty input!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "\nBackground size X: ";
		std::cin >> choice;
	}
	this->backgroundWidth = choice;

	std::cout << "\nBackground size Y: ";
	std::cin >> choice;
	while (std::cin.fail() || choice < Wingman::backgroundSize) {
		std::cout << "\nFaulty input!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "\nBackground size Y: ";
		std::cin >> choice;
	}
	this->backgroundHeight = choice;

	this->stage->setBackground(this->backgroundIndex, this->backgroundWidth, this->backgroundHeight);
	std::cin.ignore(100, '\n');
	std::cout << "\n";
}

void GameMapMaker::setEnemySpawner() {
	std::cout << "\nSet enemy spawner\n";
	std::cout << "\nRandom position: ";
	std::cin >> this->enemyRandomSpawnPos;
	while (std::cin.fail() || this->enemyRandomSpawnPos < 0 || this->enemyRandomSpawnPos > 1) {
		std::cout << "\nFaulty input!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Random position: ";
		std::cin >> this->enemyRandomSpawnPos;
	}
	std::cout << "\nType: ";
	std::cin >> this->enemyType;
	while (std::cin.fail()) {
		std::cout << "\nFaulty input!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Type: ";
		std::cin >> this->enemyType;
	}
	std::cout << "\nLevel Interval: ";
	std::cin >> this->enemyLevelInterval;
	while (std::cin.fail()) {
		std::cout << "\nFaulty input!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Level Interval: ";
		std::cin >> this->enemyLevelInterval;
	}
	std::cout << "\nNumber of enemies: ";
	std::cin >> this->nrOfEnemies;
	while (std::cin.fail() || this->nrOfEnemies < 0) {
		std::cout << "\nFaulty input!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Number of enemies: ";
		std::cin >> this->nrOfEnemies;
	}
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

void GameMapMaker::initialize() {
	// Init view
	this->initView();

	// Init textures
	this->initTextures();

	// Init map
	this->initMap();

	// Init text
	this->initText();

	// Init buttons
	this->initButtons();

	// Init UI
	this->initUI();
}

void GameMapMaker::initView() {
	this->mainView.setSize(Vector2f(this->window->getSize()));
	this->mainView.setCenter(Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2));
}

void GameMapMaker::initTextures() {
	// Map
	// Stage::initTextures();
	// Tile::initTextures();
}

void GameMapMaker::initMap() {
	this->stageName = "EMPTY";
	this->stage = new Stage(10, 10);
}

void GameMapMaker::initText() {
	// Init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	// Selector text
	this->selectorText.setString("NONE");
	this->selectorText.setFont(this->font);
	this->selectorText.setCharacterSize(14);
	this->selectorText.setFillColor(Color::White);
	this->selectorText.setPosition(Vector2f(this->mousePosWindow));

	// Enemyspawner text
	this->enemySpawnerText.setString("NONE");
	this->enemySpawnerText.setFont(this->font);
	this->enemySpawnerText.setCharacterSize(14);
	this->enemySpawnerText.setFillColor(Color::White);
	this->enemySpawnerText.setPosition(Vector2f(this->mousePosWindow));
}

void GameMapMaker::initButtons() {
	WButton temp(this->font, "EnemySpawnerSelect", 12, Vector2f(600, 600), 0);
	this->buttons.add(temp);
}

void GameMapMaker::initUI() {
	this->windowUI = true;

	this->textureX = 0;
	this->textureY = 0;
	this->selector.setSize(Vector2f(Wingman::gridSize, Wingman::gridSize));
	this->selector.setFillColor(Color::Transparent);
	this->selector.setOutlineColor(Color::Red);
	this->selector.setOutlineThickness(2.f);

	this->textureSelector.setTexture(Tile::textures);
}



void GameMapMaker::update(const float& dt) {
	// Timers update
	this->updateTimers(dt);

	// Mouse positions
	this->updateMousePositions();
	
	// Fullscreen
	this->toggleFullscreen();

	// General controls
	this->updateControls();

	// Map
	this->mapUpdate(dt);

	// Text update
	this->updateText();

	// Button update
	this->updateButtons();

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

	if (this->windowUI) {
		this->mousePosGrid.x = this->mousePosWindow.x / (Wingman::gridSize + 1);
		this->mousePosGrid.y = this->mousePosWindow.y / (Wingman::gridSize + 1);
	}
	else {
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
}

void GameMapMaker::mapUpdate(const float &dt) {
	this->stage->update(dt, this->mainView, true);
}

void GameMapMaker::updateControls() {
	// Switch Window/View UI
	if (Keyboard::isKeyPressed(Keyboard::Tab) && this->keyTime >= this->keyTimeMax) {
		if (this->windowUI)
			this->windowUI = false;
		else
			this->windowUI = true;

		this->keyTime = 0.f;
	}
	// Add/Remove tiles
	if (this->windowUI) {
		// Select texture
		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->textureX = this->mousePosGrid.x * (Wingman::gridSize + 1);
			this->textureY = this->mousePosGrid.y * (Wingman::gridSize + 1);
		}
	}
	else {
		GameMapMaker::updateAddRemoveTiles();
	}
	// New stage
	if (Keyboard::isKeyPressed(Keyboard::N) && 
		Keyboard::isKeyPressed(Keyboard::LControl) &&
		this->keyTime >= this->keyTimeMax) {
		this->newStage();
		this->keyTime = 0.f;
	}
	// enabled/disabed background stages
	if (Keyboard::isKeyPressed(Keyboard::B) && 
		Keyboard::isKeyPressed(Keyboard::LControl) &&
		this->keyTime >= this->keyTimeMax) {
		if (this->toolSelect == Stage::tileType::backgroundTile)
			this->toolSelect = Stage::tileType::regularTile;
		else
			this->toolSelect = Stage::tileType::backgroundTile;
		this->keyTime = 0.f;
	}
	// Select background
	if (Keyboard::isKeyPressed(Keyboard::G) &&
		Keyboard::isKeyPressed(Keyboard::LControl) &&
		this->keyTime >= this->keyTimeMax) {
		this->setBackground();
		this->keyTime = 0.f;
	}
	// Set enemyspawner
	if (Keyboard::isKeyPressed(Keyboard::E) &&
		Keyboard::isKeyPressed(Keyboard::LControl) &&
		Keyboard::isKeyPressed(Keyboard::LShift) &&
		this->keyTime >= this->keyTimeMax) {
		this->setEnemySpawner();
		this->keyTime = 0.f;
	}
	// Select enemyspawner
	if (Keyboard::isKeyPressed(Keyboard::E) &&
		Keyboard::isKeyPressed(Keyboard::LControl) &&
		this->keyTime >= this->keyTimeMax) {
		this->toolSelect = Stage::tileType::enemySpawner;
		this->keyTime = 0.f;
	}
	// Save stage
	if (Keyboard::isKeyPressed(Keyboard::S) && 
		Keyboard::isKeyPressed(Keyboard::LControl) &&
		this->keyTime >= this->keyTimeMax) {
		this->saveStage();
		this->keyTime = 0.f;
	}
	// Load stage
	if (Keyboard::isKeyPressed(Keyboard::L) && 
		Keyboard::isKeyPressed(Keyboard::LControl) &&
		this->keyTime >= this->keyTimeMax) {
		this->loadStage();
		this->keyTime = 0.f;
	}
}

void GameMapMaker::updateAddRemoveTiles() {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (this->toolSelect == Stage::tileType::regularTile ||
			this->toolSelect == Stage::tileType::backgroundTile
			) {
			this->stage->addTile(
				Tile(IntRect(this->textureX, this->textureY,
					Wingman::gridSize, Wingman::gridSize),
					Vector2f(this->mousePosGrid.x * Wingman::gridSize,
						this->mousePosGrid.y * Wingman::gridSize),
					false,
					false
				),
				this->mousePosGrid.x,
				this->mousePosGrid.y,
				this->toolSelect
			);
		}
		else if (this->toolSelect == Stage::tileType::enemySpawner) {
			this->enemyPosGrid = this->mousePosGrid;
			this->stage->addEnemySpawner(
				EnemySpawner(
					this->enemyPosGrid,
					this->enemyRandomSpawnPos,
					this->enemyType,
					this->enemyLevelInterval,
					this->nrOfEnemies
				),
				this->mousePosGrid.x,
				this->mousePosGrid.y
			);
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Right)) {
		if (this->toolSelect == Stage::tileType::regularTile ||
			this->toolSelect == Stage::tileType::backgroundTile) {
			this->stage->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, this->toolSelect);
		}
		else if (this->toolSelect == Stage::tileType::enemySpawner) {
			this->stage->removeEnemySpawner(this->mousePosGrid.x, this->mousePosGrid.y);
		}
	}
}

void GameMapMaker::updateText() {
	if(this->windowUI) {
		this->selectorText.setPosition(Vector2f(this->mousePosWindow.x + 20.f, this->mousePosWindow.y));
		this->enemySpawnerText.setPosition(Vector2f(this->mousePosWindow.x + 20.f, this->mousePosWindow.y + 20.f));
	}
	else {
		this->selectorText.setPosition(Vector2f(this->mousePosWorld.x + 20.f, this->mousePosWorld.y));
		this->enemySpawnerText.setPosition(Vector2f(this->mousePosWorld.x + 20.f, this->mousePosWorld.y + 20.f));
	}
		
	if (this->toolSelect == Stage::tileType::backgroundTile)
		this->selectorText.setString("BACKGROUND");
	else if(this->toolSelect == Stage::tileType::regularTile)
		this->selectorText.setString("REGULAR TILE");
	else if (this->toolSelect == Stage::tileType::enemySpawner)
		this->selectorText.setString("ENEMY SPAWNER");

	this->enemySpawnerText.setString(
		"Random pos: " + std::to_string(this->enemyRandomSpawnPos) +
		"\nType: " + std::to_string(this->enemyType) +
		"\nLevel Interval: " + std::to_string(this->enemyLevelInterval));
}

void GameMapMaker::updateButtons() {
	for (size_t i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].update(this->mousePosWorld);
	}
}

void GameMapMaker::updateUI() {
	if (this->windowUI) {
		this->selector.setPosition(
			this->mousePosGrid.x * (Wingman::gridSize + 1),
			this->mousePosGrid.y * (Wingman::gridSize + 1));
	}
	else {
		this->selector.setPosition(
			this->mousePosGrid.x * Wingman::gridSize,
			this->mousePosGrid.y * Wingman::gridSize);
	}
}

void GameMapMaker::updateView(const float &dt) {
	float speed = 0.f;
	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		speed = 40.f;
	}
	else { 
		speed = 20.f; 
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->mainView.move(0.f, -speed * dt * this->dtMultiplier);
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->mainView.move(0.f, speed * dt * this->dtMultiplier);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		this->mainView.move(-speed * dt * this->dtMultiplier, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		this->mainView.move(speed * dt * this->dtMultiplier, 0.f);
	}
}



void GameMapMaker::draw() {
	// Clear
	this->window->clear();

	// Set view;
	this->window->setView(this->mainView);

	// Draw map
	this->drawMap();

	// Draw text
	this->drawText();

	// Set view;
	if (this->windowUI) {
		this->window->setView(this->window->getDefaultView());
		this->drawUIWindow();
	}
	else {
		this->window->setView(this->mainView);
		this->drawUIView();
	}

	// Finish draw
	this->window->display();
}


void GameMapMaker::drawText() {
	this->window->draw(this->selectorText);
	this->window->draw(this->enemySpawnerText);
}

void GameMapMaker::drawMap() {
	this->stage->draw(*this->window, this->mainView, true, this->font);
}

void GameMapMaker::drawUIWindow() {
	this->window->draw(this->textureSelector);
	this->window->draw(this->selector);
}

void GameMapMaker::drawUIView() {
	this->window->draw(this->selector);
	for (size_t i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].draw(*this->window);
	}
}

