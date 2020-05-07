#pragma once

#include"Tile.h"

class Stage {
public:
	Stage();
	virtual ~Stage();

	dArr<dArr<Tile>>& getTiles() { return this->tiles; }

	void update(
		int fromCol, int toCol,
		int fromRow, int toRow
	);
	void draw(
		RenderTarget& target, 
		View &view);

	// Static variables
	static int gridSize;

private:
	dArr<dArr<Tile>> tiles;
	
	unsigned long stageSizeX; 
	unsigned long stageSizeY;

	// Optimization
	int fromCol, toCol;
	int fromRow , toRow;
};