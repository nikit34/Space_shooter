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


enum powerupTypes { RF = 0, XP2 };

class Powerup {
public:
	Powerup(
		int type, 
		float timerMax, 
		Vector2f pos
	);

	virtual ~Powerup();

	// Accessors
	inline int getType()const { return this->type; }
	inline bool isActive()const { return this->timer > 0; }
	inline Vector2f pos()const { return this->sprite.getPosition(); }
	inline FloatRect getBounds()const { return this->sprite.getGlobalBounds(); }
	inline bool collide(FloatRect rect)const { return this->sprite.getGlobalBounds().intersects(rect); }
	inline bool canRemove()const { return this->timer <= 0.f; }

	// Functions
	void update(const float &dt);
	void draw(RenderTarget &target);

	// Static
	static int nrOfPowerups;
	static dArr<Texture> powerupTextures;

private:
	float dtMultiplier;
	
	Sprite sprite;
	
	float timerMax;
	float timer;
	int type;
};

