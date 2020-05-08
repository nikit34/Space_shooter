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

class Particle {
public:
	float dtMultiplier;
	Sprite sprite;
	Vector2f dir;
	float maxVel;
	float maxRotation;
	float lifeTime;

	Particle(
		Vector2f pos,
		int textureIndex,
		Vector2f dir,
		float maxVel,
		float maxRotation,
		float lifeTime
	);
	~Particle();

	inline bool readyToDel() const { return this->lifeTime <= 0.f; }
	void update(const float& dt);
	void draw(RenderTarget& target);

	static dArr<Texture> particleTextures;

private:

};
