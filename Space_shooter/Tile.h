#pragma once

#include"SFML\Audio.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\System.hpp"
#include<iostream>
#include<vector>
#include<cstdlib>
#include<math.h>
#include<fstream>
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
	inline const bool getisDamaging()const { return this->isDamaging; }
	inline const bool getisCollider()const { return this->isCollider; }

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

