#pragma once

#include"TileArr.h"

class Stage {
public:
	Stage(unsigned long sizeX, unsigned long sizeY);
	virtual ~Stage();

	TileArr<TileArr<Tile>>& getTiles() { return this->tiles; }

	// Accessors
	inline int getSizeX()const { return this->stageSizeX; }
	inline int getSizeY()const { return this->stageSizeY; }

	void addTile(const Tile tile, unsigned row, unsigned col);
	void removeTile(unsigned row, unsigned col);

	void saveStage(std::string fileName);
	bool loadStage(std::string fileName);

	void updateBackground(const float& dt, Vector2f pos);
	void update(
		int fromCol, int toCol,
		int fromRow, int toRow);

	void draw(
		RenderTarget& target, 
		View &view);

private:	
	float dtMultiplier;
	unsigned long stageSizeX; 
	unsigned long stageSizeY;

	TileArr<TileArr<Tile>> tiles;
	
	Sprite backgroundTilesSprite;
	Image backgroundTilesImage;
	Texture backgroundTilesTexture;
	Texture backgroundTexture;
	Sprite background1;
	Sprite background2;

	// Optimization
	int fromCol, toCol;
	int fromRow , toRow;
};