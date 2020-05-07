#include"Stage.h"

int Stage::gridSize = 50;

Stage::Stage() {
	this->stageSizeX = 100;
	this->stageSizeY = 100;

	this->fromCol = 0;
	this->toCol = 0;
	this->fromRow = 0;
	this->toRow = 0;
	
	for (size_t i = 0; i < this->stageSizeX; i++) {
		this->tiles.add(dArr<Tile>(stageSizeY));

		for (size_t k = 0; k < this->stageSizeY; k++) {
			if (rand() % 50 > 10)
				this->tiles[i].add(Tile(IntRect(0, 0, 0, 0), Vector2f(i * Stage::gridSize, k * Stage::gridSize), 0, 0));
			else
				this->tiles[i].add(Tile(IntRect(0, 0, 50, 50), Vector2f(i * Stage::gridSize, k * Stage::gridSize), 0, 0));

		}
	}
}

Stage::~Stage() {}

void Stage::update(
	int fromCol, int toCol,
	int fromRow, int toRow
) {

}

void Stage::draw(
	RenderTarget& target, 
	View& view
) {
	this->fromCol = (view.getCenter().x - view.getSize().x / 2) / Stage::gridSize;
	if (this->fromCol <= 0)
		this->fromCol = 0;
	if (this->fromCol >= this->stageSizeX)
		this->fromCol = this->stageSizeX;

	this->toCol = (view.getCenter().x + view.getSize().x / 2) / Stage::gridSize + 1;
	if (this->toCol <= 0)
		this->toCol = 0;
	if (this->toCol >= this->stageSizeX)
		this->toCol = this->stageSizeX;
	
	this->fromRow = (view.getCenter().y - view.getSize().y / 2) / Stage::gridSize;
	if (this->fromRow <= 0)
		this->fromRow = 0;
	if (this->fromRow >= this->stageSizeY)
		this->fromRow = this->stageSizeY;

	this->toRow = (view.getCenter().y + view.getSize().y / 2) / Stage::gridSize + 1;
	if (this->toRow <= 0)
		this->toRow = 0;
	if (this->toRow >= this->stageSizeY)
		this->toRow = this->stageSizeY;

	for (size_t i = fromCol; i < toCol; i++) {
		for (size_t k = fromRow; k < toRow; k++) {
			this->tiles[i][k].draw(target);
		}
	}
}