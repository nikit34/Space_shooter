#include"Stage.h"


Stage::Stage(unsigned long sizeX, unsigned long sizeY)
	:stageSizeX(sizeX), stageSizeY(sizeY), 
	tiles(stageSizeX)
{
	this->dtMultiplier = 60.f;

	this->fromCol = 0;
	this->toCol = 0;
	this->fromRow = 0;
	this->toRow = 0;

	for (unsigned i = 0; i < this->stageSizeX; i++) {
		this->tiles.push(TileArr<Tile>(stageSizeY), i);
	}
}

Stage::~Stage() {}

void Stage::addTile(const Tile tile, unsigned row, unsigned col) {
	if (row >= this->stageSizeX || col >= this->stageSizeY)
		throw("OUT OF BOUNDS STAGE ADDTILE");
	
	if (this->tiles[row].isNull(col))
		this->tiles[row].push(tile, col);
	else
		std::cout << "Already tile in that position\n";
}

void Stage::removeTile(unsigned row, unsigned col) {
	if (row >= this->stageSizeX || col >= this->stageSizeY)
		throw("OUT OF BOUNDS STAGE REMOVETILE");

	if (!this->tiles[row].isNull(col))
		this->tiles[row].remove(col);	
	else
		std::cout << "No tile in that position\n";
}

void Stage::saveStage(std::string fileName) {
	std::ofstream out;
	out.open(fileName.c_str());
	if (out.is_open()) {
		// Save map size
		out << std::to_string(this->stageSizeX) << " ";
		out << std::to_string(this->stageSizeY) << " ";

		// Save background path
		out << "NONE ";
		out << "\n";
		for (size_t i = 0; i < this->stageSizeX; i++) {
			for (size_t k = 0; k < this->stageSizeY; k++) {
				if(!this->tiles[i].isNull(k))
					out << this->tiles[i][k].getAsString() << " ";
			}
		}
		out << "\n";
	}
	else {
		std::cout << "\nCould not open map file\n";
	}
	out.close();
}

bool Stage::loadStage(std::string fileName) {
	std::ifstream in;
	bool loadSuccess = false;

	unsigned sizeX = 0;
	unsigned sizeY = 0;
	std::string backgroundPath;
	int rectLeft = 0;
	int rectTop = 0;
	int rectWidth = 0;
	int rectHeight = 0;
	int gridPosX = 0;
	int gridPosY = 0;
	int isCollider = 0;
	int isDamaging = 0;
	int damage = 0;

	// Open file
	in.open(fileName);
	if (in.is_open()) {
		in >> sizeX >> sizeY;
		this->stageSizeX = sizeX;
		this->stageSizeY = sizeY;
		
        in >> backgroundPath;
		this->backgroundTexture.loadFromFile(backgroundPath);
		this->background1.setTexture(this->backgroundTexture);
		this->background2.setTexture(this->backgroundTexture);

		// Clear old stage
		this->tiles.resizeClear(this->stageSizeX);
		for (size_t i = 0; i < this->stageSizeX; i++) {
			this->tiles.push(TileArr<Tile>(stageSizeY), i);
		}
		std::cout << "\nCleared\n";

		// Load new stage
		while (in >> 
			rectLeft >> rectTop >> rectWidth >> rectHeight >> 
			gridPosX >> gridPosY >> 
			isCollider >> isDamaging >> damage
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
		in.ignore();
		loadSuccess = true;
	}
	else {
		loadSuccess = false;
	}
	in.close();
	return loadSuccess;
}

void Stage::updateBackground(float const& dt, Vector2f pos) {

}

void Stage::update(
	int fromCol, int toCol,
	int fromRow, int toRow
) {

}

void Stage::draw(
	RenderTarget& target, 
	View& view
) {
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

	for (int i = fromCol; i < toCol; i++) {
		for (int k = fromRow; k < toRow; k++) {
			if(!this->tiles[i].isNull(k))
				this->tiles[i][k].draw(target);
		}
	}
}