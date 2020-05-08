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
	Vector2f currentVel;
	float maxVel;
	float deceleration;
	float maxRotation;
	float lifeTimeMax;
	float lifeTime;
	Color color;

	Particle(
		Vector2f pos,
		int textureIndex,
		Vector2f dir,
		float maxVel,
		float maxRotation,
		float lifeTime,
		Color color
	);
	~Particle();

	inline bool readyToDel() const { return this->lifeTime <= 0.f; }
	void update(const float& dt);
	void draw(RenderTarget& target);

	static dArr<Texture> particleTextures;

	//Regular functions
	float vectorLength(Vector2f v) {
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}

	Vector2f normalize(Vector2f v, float length) {
		if (length == 0)
			return Vector2f(0.f, 0.f);
		else
			return v / length;
	}
};
