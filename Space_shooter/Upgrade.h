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
		Vector2f position,
		int type,
		float aliveTimerMax
	);
	virtual ~Upgrade();

	inline const int& getType() { return this->type; }
	inline bool canDelete() { return this->aliveTimer >= this->aliveTimerMax; }

	bool checkCollision(FloatRect rect);

	void update(const float& dt);
	void draw(RenderTarget& target);

	// Static
	static int nrOfUpgrades;
	static dArr<Texture> upgradeTextures;

private:
	float dtMultiplier;

	int type;
	
	float aliveTimer;
	float aliveTimerMax;

	Sprite sprite;
};