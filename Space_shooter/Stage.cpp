#include"Stage.h"


// Static define
dArr<Texture> Stage::textures;
int Stage::nrOfTextures;
void Stage::initTextures() {
	Texture temp;
	std::string tempStr;
	std::ifstream in;

	in.open("Textures/Backgrounds/backgrounds.txt");
	if (in.is_open()) {
		while (std::getline(in, tempStr)) {
			temp.loadFromFile(tempStr.c_str());
			temp.setRepeated(true);
			Stage::textures.add(Texture(temp));
			tempStr.clear();
		}
	}
	in.close();

	Stage::nrOfTextures = Stage::textures.size();
}

Stage::Stage(unsigned long sizeX, unsigned long sizeY)
	:stageSizeX(sizeX), stageSizeY(sizeY), 
	tiles(stageSizeX),
	backgroundTiles(stageSizeX),
	enemySpawners(stageSizeX)
{
	this->dtMultiplier = 60.f;

	this->fromCol = 0;
	this->toCol = 0;
	this->fromRow = 0;
	this->toRow = 0;

	this->scrollSpeed = 0.5f;

	for (unsigned i = 0; i < this->stageSizeX; i++) {
		this->tiles.push(TileArr<Tile>(stageSizeY), i);
		this->backgroundTiles.push(TileArr<Tile>(stageSizeY), i);
		this->enemySpawners.push(TileArr<EnemySpawner>(stageSizeY), i);
	}
	this->backgroundIndex = 0;
	this->background.setSize(Vector2f(Wingman::backgroundSize, Wingman::backgroundSize));
	this->background.setTextureRect(IntRect(0, 0, Wingman::backgroundSize, Wingman::backgroundSize));
	this->background.setTexture(&Stage::textures[this->backgroundIndex]);
}

Stage::~Stage() {}

void Stage::addTile(const Tile tile, unsigned row, unsigned col, int type) {
	if (row >= this->stageSizeX || col >= this->stageSizeY)
		throw("OUT OF BOUNDS STAGE ADDTILE");
	
	if (type == tileType::regularTile) {
		if (this->tiles[row].isNull(col))
			this->tiles[row].push(tile, col);
		else
			std::cout << "Already tile in that position\n";
	}
	else if (type == tileType::backgroundTile) {
		if (this->backgroundTiles[row].isNull(col)) {
			this->backgroundTiles[row].push(Tile(tile.getTexRect(), tile.getPos(), false, false), col);
			this->backgroundTiles[row][col].setColor(Color(100, 100, 100, 255));
		}
		else
			std::cout << "Already background tile in that position\n";
	}
}

void Stage::removeTile(unsigned row, unsigned col, bool background) {
	if (row >= this->stageSizeX || col >= this->stageSizeY)
		throw("OUT OF BOUNDS STAGE REMOVETILE");

	if (!background) {
		if (!this->tiles[row].isNull(col))
			this->tiles[row].remove(col);
		else
			std::cout << "No tile in that position\n";
	}
	else {
		if (!this->backgroundTiles[row].isNull(col))
			this->backgroundTiles[row].remove(col);
		else
			std::cout << "No background tile in that position\n";
	}
}

void Stage::addEnemySpawner(const EnemySpawner es, unsigned row, unsigned col) {
	if (this->enemySpawners[row].isNull(col))
		this->enemySpawners[row].push(es, col);
	else
		std::cout << "Already enemyspawner in that position\n";
}

void Stage::removeEnemySpawner(unsigned row, unsigned col) {
	if (row >= this->stageSizeX || col >= this->stageSizeY)
		throw("OUT OF BOUNDS STAGE REMOVEENEMYSPAWNER");

	if (!this->enemySpawners[row].isNull(col))
			this->enemySpawners[row].remove(col);
		else
			std::cout << "No enemy spawner in that position\n";
}

void Stage::reset(View& view) {
	this->backgrounds.clear();
	this->background.setPosition(Vector2f(
		view.getCenter().x - view.getSize().x / 2, 
		view.getCenter().y - view.getSize().y / 2));
	this->backgrounds.add(this->background);
}

void Stage::setBackground(const int index, const int width, const int height) {
	if (index >= 0 && index < Stage::nrOfTextures) {
		this->backgroundIndex = index;
		this->background.setSize(Vector2f(width, height));
		this->background.setTextureRect(IntRect(0, 0, width, height));
		this->background.setTexture(&Stage::textures[index]);
	}
}

void Stage::setBackgroundSize(float width, float height) {
	if (width < Wingman::backgroundSize || height < Wingman::backgroundSize) {
		width = Wingman::backgroundSize;
		height = Wingman::backgroundSize;
	}
	this->background.setSize(Vector2f(width, height));
}

void Stage::saveStage(std::string fileName) {
	std::ofstream out;
	out.open(fileName.c_str());
	
	if (out.is_open()) {
		// Save map size
		out << std::to_string(this->stageSizeX) << " ";
		out << std::to_string(this->stageSizeY) << " ";

		// Save background path
		out << this->backgroundIndex 
			<< " " << static_cast<int>(this->background.getGlobalBounds().width) 
			<< " " << static_cast<int>(this->background.getGlobalBounds().height);
		out << "\n";
		for (size_t i = 0; i < this->stageSizeX; i++) {
			// Regular tiles
			for (size_t k = 0; k < this->stageSizeY; k++) {
				if (!this->tiles[i].isNull(k))
					out << this->tiles[i][k].getAsString() << " ";
			}
		}
		out << "\n";
		for (size_t i = 0; i < this->stageSizeX; i++) {
			// Regular background tiles
			for (size_t k = 0; k < this->stageSizeY; k++) {
				if (!this->backgroundTiles[i].isNull(k))
					out << this->backgroundTiles[i][k].getAsString() << " ";
			}
		}
		out << "\n";
		for (size_t i = 0; i < this->stageSizeX; i++) {
			// Enemyspawners
			for (size_t k = 0; k < this->stageSizeY; k++) {
				if (!this->enemySpawners[i].isNull(k))
					out << this->enemySpawners[i][k].getAsString() << " ";
			}
		}
	}
	else {
		std::cout << "\nCould not open map file " << fileName << "\n";
	}
	out.close();
}

bool Stage::loadStage(std::string fileName, View& view) {
	std::ifstream in;
	bool loadSuccess = false;

	std::stringstream ss;
	std::string line = "";

	// Map
	unsigned sizeX = 0;
	unsigned sizeY = 0;
	
	// Background
	int bgIndex = 0;
	int bgWidth = 0;
	int bgHeight = 0;

	// Tiles
	int rectLeft = 0;
	int rectTop = 0;
	int rectWidth = 0;
	int rectHeight = 0;
	int gridPosX = 0;
	int gridPosY = 0;
	int isCollider = 0;
	int isDamaging = 0;

	// Enemyspawner
	int type = 0;
	int levelInterval = 0;
	int nrOfEnemies = 0;
	float spawnTimerMax = 0.f;

	// Open file
	in.open(fileName);
	if (in.is_open()) {
		// Load basics
		std::getline(in, line);
		ss.str(line);

		ss >> sizeX >> sizeY >> bgIndex >> bgWidth >> bgHeight;
		this->stageSizeX = sizeX;
		this->stageSizeY = sizeY;

		this->backgroundIndex = bgIndex;
		this->background.setSize(Vector2f(bgWidth, bgHeight));
		this->background.setTextureRect(IntRect(0, 0, bgWidth, bgHeight));
		this->background.setTexture(&Stage::textures[bgIndex]);
		this->backgrounds.add(this->background);

		// Clear old stage
		this->tiles.resizeClear(this->stageSizeX);
		this->backgroundTiles.resizeClear(this->stageSizeX);
		this->enemySpawners.resizeClear(this->stageSizeX);

		for (size_t i = 0; i < this->stageSizeX; i++) {
			this->tiles.push(TileArr<Tile>(stageSizeY), i);
			this->backgroundTiles.push(TileArr<Tile>(stageSizeY), i);
			this->enemySpawners.push(TileArr<EnemySpawner>(stageSizeY), i);
		}
		line.clear();
		ss.clear();

		// Load regular tiles
		std::getline(in, line);
		ss.str(line);

		while (ss >> 
			rectLeft >> rectTop >> rectWidth >> rectHeight >> 
			gridPosX >> gridPosY >> 
			isCollider >> isDamaging
		) {
			this->tiles[gridPosX].push(
				Tile(
					IntRect(rectLeft, rectTop, rectWidth, rectHeight),
					Vector2f(gridPosX * Wingman::gridSize, gridPosY * Wingman::gridSize),
					isCollider,
					isDamaging),
				gridPosY
			);
		}
		line.clear();
		ss.clear();

		// Load background tiles
		std::getline(in, line);
		ss.str(line);

		while (ss >> 
			rectLeft >> rectTop >> rectWidth >> rectHeight >> 
			gridPosX >> gridPosY >> 
			isCollider >> isDamaging
		) {
			this->backgroundTiles[gridPosX].push(
				Tile(
					IntRect(rectLeft, rectTop, rectWidth, rectHeight),
					Vector2f(gridPosX * Wingman::gridSize, gridPosY * Wingman::gridSize),
					isCollider,
					isDamaging),
				gridPosY
			);
			this->backgroundTiles[gridPosX][gridPosY].setColor(Wingman::backgroundColor);
		}

		// Enemy spawners
		std::getline(in, line);
		ss.str(line);

		while (ss >>
			gridPosX >> gridPosY >> type >> levelInterval >>
			nrOfEnemies >> spawnTimerMax
			) {
			this->enemySpawners[gridPosX].push(
				EnemySpawner(
					Vector2i(gridPosX, gridPosY),
					type,
					levelInterval,
					nrOfEnemies,
					spawnTimerMax
				),
				gridPosY
			);
		}

		loadSuccess = true;
	}
	else {
		loadSuccess = false;
	}
	in.close();
	return loadSuccess;
}

void Stage::updateBackground(const float& dt, View& view) {
	bool bgRemoved = false;
	for (size_t i = 0; i < this->backgrounds.size() && !bgRemoved; i++) {
		this->backgrounds[i].move(this->scrollSpeed * dt * this->dtMultiplier, 0.f);

		if (this->backgrounds.size() < 3 &&
			this->backgrounds[i].getPosition().x + this->backgrounds[i].getGlobalBounds().width
			<=
			view.getCenter().x + view.getSize().x / 2) {
			this->background.setPosition(
				this->backgrounds[i].getPosition().x + this->backgrounds[i].getGlobalBounds().width,
				this->background.getPosition().y);
			this->backgrounds.add(this->background);
		}
		// Remove background
		else if (this->backgrounds[i].getPosition().x + this->backgrounds[i].getGlobalBounds().width 
			<= 
			view.getCenter().x - view.getSize().x / 2) {
			bgRemoved = true;
		}
		if (bgRemoved) {
			this->backgrounds.remove(i);
		}
	}
}

void Stage::update(const float& dt, View& view, bool editor) {
	//this->fromCol = (view.getCenter().x - view.getSize().x / 2) / Wingman::gridSize;
	//if (fromCol <= 0)
	//	fromCol = 0;
	//if (fromCol >= this->stageSizeX)
	//	fromCol = this->stageSizeX;

	//this->toCol = (view.getCenter().x + view.getSize().x / 2) / Wingman::gridSize + 1;
	//if (toCol <= 0)
	//	toCol = 0;
	//if (toCol >= this->stageSizeX)
	//	toCol = this->stageSizeX;

	//this->fromRow = (view.getCenter().y - view.getSize().y / 2) / Wingman::gridSize;
	//if (fromRow <= 0)
	//	fromRow = 0;
	//if (fromRow >= this->stageSizeY)
	//	fromRow = this->stageSizeY;

	//this->toRow = (view.getCenter().y + view.getSize().y / 2) / Wingman::gridSize + 1;
	//if (toRow <= 0)
	//	toRow = 0;
	//if (toRow >= this->stageSizeY)
	//	toRow = this->stageSizeY;

	//// Tiles
	//for (int i = fromCol; i < toCol; i++) {
	//	for (int k = fromRow; k < toRow; k++) {

	//		if (!this->backgroundTiles[i].isNull(k))
	//			this->backgroundTiles[i][k].update(dt);

	//		if (!this->tiles[i].isNull(k))
	//			this->tiles[i][k].update(dt);

	//		if (!this->enemySpawners[i].isNull(k))
	//			this->enemySpawners[i][k].update(dt);

	//		this->updateBackground(dt, i, k);
	//	}
	//}
	if(!editor)
		this->updateBackground(dt, view);
}

void Stage::draw(
	RenderTarget& target, 
	View& view, 
	bool editor,
	Font& font
) {
	// Index calculations
	this->fromCol = (view.getCenter().x - view.getSize().x / 2) / Wingman::gridSize;
	if (fromCol <= 0)
		fromCol = 0;
	if (fromCol >= this->stageSizeX)
		fromCol = this->stageSizeX;

	this->toCol = (view.getCenter().x + view.getSize().x / 2) / Wingman::gridSize + 1;
	if (toCol <= 0)
		toCol = 0;
	if (toCol >= this->stageSizeX)
		toCol = this->stageSizeX;
	
	this->fromRow = (view.getCenter().y - view.getSize().y / 2) / Wingman::gridSize;
	if (fromRow <= 0)
		fromRow = 0;
	if (fromRow >= this->stageSizeY)
		fromRow = this->stageSizeY;

	this->toRow = (view.getCenter().y + view.getSize().y / 2) / Wingman::gridSize + 1;
	if (toRow <= 0)
		toRow = 0;
	if (toRow >= this->stageSizeY)
		toRow = this->stageSizeY;

	// Background
	if (editor) {
		target.draw(this->background);
	}
	else {
		for (size_t i = 0; i < this->backgrounds.size(); i++) {
			target.draw(this->backgrounds[i]);
		}
	}
	// Tiles
	for (int i = fromCol; i < toCol; i++) {
		for (int k = fromRow; k < toRow; k++) {
			if(!this->backgroundTiles[i].isNull(k))
				this->backgroundTiles[i][k].draw(target);
			if (!this->tiles[i].isNull(k))
				this->tiles[i][k].draw(target);
			// EnemySpawner
			if (!this->enemySpawners[i].isNull(k) && editor)
				this->enemySpawners[i][k].draw(target, font);
		}
	}
}