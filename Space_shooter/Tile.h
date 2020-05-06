#pragma once

#include"SFML\Audio.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\System.hpp"
#include<iostream>
#include<vector>
#include<cstdlib>
#include<math.h>
#include<fstream>
#include<sstream>
#include"dArr.h"

using namespace sf;

class Tile {
public:
	Tile(
		IntRect textureRect,
		Vector2f pos,
		bool isCollider,
		bool isDamaging
	);
	virtual ~Tile();

    // Static textures
	static Texture tileTextures;

	inline const Vector2f getPos()const { return this->sprite.getPosition(); }
	inline const FloatRect getBounds()const { return this->sprite.getGlobalBounds(); }
	inline const bool getIsDamaging()const { return this->isDamaging; }
	inline const bool getIsCollider()const { return this->isCollider; }
	inline void setPos(float x, float y) { this->sprite.setPosition(Vector2f(x, y)); }
	inline void setTexRect(int x, int y, int width, int height) { this->sprite.setTextureRect(IntRect(x, y, width, height)); }
	inline void setIsDamaging(bool isDamaging) { this->isDamaging = isDamaging; }
	inline void setIsCollider(bool isCollider) { this->isCollider = isCollider; }

	void update();
	void draw(RenderTarget &target);

private:
	// Core
	int type;
	bool isCollider;
	bool isDamaging;
	int damage;

	// Positioning

	// Visual
	Sprite sprite;
};

