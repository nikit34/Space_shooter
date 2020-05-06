#pragma once

#include"Tile.h"

class Stage {
public:
	Stage();
	virtual ~Stage();

	dArr<dArr<std::string>>& getTiles() { return this->tiles; }

	void update(
		int fromCol, int toCol,
		int fromRow, int toRow
	);
	void draw(RenderTarget& target, 
		int fromCol, int toCol,
		int fromRow, int toRow
	);

	// Static variables
	static int gridSize;

private:
	dArr<dArr<std::string>> tiles;
	Tile creationTile;
};