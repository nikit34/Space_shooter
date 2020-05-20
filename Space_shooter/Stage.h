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
	inline float getScrollSpeed()const { return this->scrollSpeed; }

	void addTile(const Tile tile, unsigned row, unsigned col, bool background);
	void removeTile(unsigned row, unsigned col, bool background);
	void setBackground(const int index, const int width, const int height);
	void setBackgroundSize(float width, float height);

	void saveStage(std::string fileName);
	bool loadStage(std::string fileName, View &view);

	void updateBackground(const float& dt, View& view);
	void update(float const& dt, View& view, bool editor);

	void draw(RenderTarget& target, View& view, bool editor);

	// Static
	static dArr<Texture> textures;
	static int nrOfTextures;
	static void initTextures();

private:	
	float dtMultiplier;
	unsigned long stageSizeX; 
	unsigned long stageSizeY;

	TileArr<TileArr<Tile>> tiles;
	TileArr<TileArr<Tile>> backgroundTiles;
	TileArr<TileArr<Tile>> enemySpawners;
	
	float scrollSpeed;

	int backgroundIndex;
	RectangleShape background;
	dArr<RectangleShape> backgrounds;

	// Optimization
	int fromCol, toCol;
	int fromRow , toRow;
};