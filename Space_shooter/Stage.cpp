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
}

void Stage::removeTile(unsigned row, unsigned col) {
	if (row >= this->stageSizeX || col >= this->stageSizeY)
		throw("OUT OF BOUNDS STAGE REMOVETILE");

	if (!this->tiles[row].isNull(col))
		this->tiles[row].remove(col);
}

void Stage::saveStage(std::string fileName) {

}

void Stage::loadStage(std::string fileName) {
	// Load map size

	// Set tile arr size

	// Load backgrounds

	// Load tiles
}

void Stage::updateBackground(float const& dt, Vector2f pos) {
	for (size_t i = 0; i < background.size(); i++)
	{

	}
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