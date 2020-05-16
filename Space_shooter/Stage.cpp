#include"Stage.h"


Stage::Stage(unsigned long sizeX, unsigned long sizeY)
	:stageSizeX(sizeX), stageSizeY(sizeY), 
	tiles(stageSizeX) 
{
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
	if (this->tiles[row].isNull(col))
		this->tiles[row].push(tile, col);
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
	if (this->fromCol <= 0)
		this->fromCol = 0;
	if (this->fromCol >= this->stageSizeX)
		this->fromCol = this->stageSizeX;

	this->toCol = (view.getCenter().x + view.getSize().x / 2) / Wingman::gridSize + 1;
	if (this->toCol <= 0)
		this->toCol = 0;
	if (this->toCol >= this->stageSizeX)
		this->toCol = this->stageSizeX;
	
	this->fromRow = (view.getCenter().y - view.getSize().y / 2) / Wingman::gridSize;
	if (this->fromRow <= 0)
		this->fromRow = 0;
	if (this->fromRow >= this->stageSizeY)
		this->fromRow = this->stageSizeY;

	this->toRow = (view.getCenter().y + view.getSize().y / 2) / Wingman::gridSize + 1;
	if (this->toRow <= 0)
		this->toRow = 0;
	if (this->toRow >= this->stageSizeY)
		this->toRow = this->stageSizeY;

	for (int i = fromCol; i < toCol; i++) {
		for (int k = fromRow; k < toRow; k++) {
			if(!this->tiles[i].isNull(k))
				this->tiles[i][k].draw(target);
		}
	}
}