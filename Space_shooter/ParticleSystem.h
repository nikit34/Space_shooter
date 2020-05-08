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

class ParticleSystem {
public:
	ParticleSystem();
	virtual ~ParticleSystem();

	void update(const float& dt);
	void draw(RenderTarget& target);

	static dArr<Texture> particleTextures;

private:
	class Particle {
	public:
		Sprite sprite;
		Vector2f dir;
		float maxVel;
		float maxRotation;
		float lifeTime;

		Particle(
			float xPos,
			float yPos,
			int textureIndex,
			float xDir,
			float yDir,
			float maxVel,
			float maxRotation,
			float lifeTime,
			bool random
		) {
			this->sprite.setTexture(ParticleSystem::particleTextures[textureIndex]);
			this->sprite.setPosition(Vector2f(xPos, yPos));

			this->dir.x = xDir;
			this->dir.y = yDir;

			this->maxVel = maxVel;
			this->maxRotation = maxRotation;

			this->lifeTime = lifeTime;
		}
		~Particle() {}

	private:
	};

	dArr<Sprite> particles;
};

