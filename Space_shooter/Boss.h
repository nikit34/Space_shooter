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

class Boss {
public:
	Boss(dArr<Texture>& textures,
		Vector2f position,
		int type
	);
	virtual ~Boss();

	void Movement();
	void Update(const float& dt);
	void Draw(RenderTarget& target);


private:

	class BossGun {
	public:
		BossGun(Texture *texture, 
			Vector2f position, 
			float shootTimerMax
		) {
			this->shootTimerMax = shootTimerMax;
			this->shootTimer = this->shootTimerMax;
			
			this->gunSprite.setTexture(*texture);
			this->gunSprite.setPosition(position);
		}

		~BossGun() {

		}

	private:
		float dtMultiplier;

		Sprite gunSprite;

		float shootTimerMax;
		float shootTimer;
	};


	float dtMultiplier;
	int type;
	int nrOfGuns;

	dArr<Texture> *textures;
	Sprite sprite;
	dArr<BossGun> guns;

	int damageMax;
	int damageMin;

	int hpMax;
	int hp;
};

