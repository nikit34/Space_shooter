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

class Upgrade {
public:
	Upgrade(
		dArr<Texture>& textures, 
		Vector2f position,
		int type,
		float aliveTimerMax
	);
	virtual ~Upgrade();

	inline const int& getType() { return this->type; }
	inline bool canDelete() { return this->aliveTimer >= this->aliveTimerMax; }

	bool checkCollision(const FloatRect rect);

	void Update(const float& dt);
	void Draw(RenderTarget& target);

private:
	float dtMultiplier;

	int type;
	
	float aliveTimer;
	float aliveTimerMax;

	dArr<Texture>* textures;

	Sprite sprite;
};