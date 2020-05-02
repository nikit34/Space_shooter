#pragma once

#include"Bullet.h"

using namespace sf;

class Boss {
public:
	Boss(dArr<Texture>& bodyTextures,
		dArr<Texture>& gunTextures,
		dArr<Texture>& bulletTextures,
		Vector2f position,
		int type
	);
	virtual ~Boss();

	void movement();
	void update(const float& dt);
	void draw(RenderTarget& target);

private:

	class BossGun {
	public:
		BossGun(Texture* texture,
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

		void update(const float &dt) {

		}

		void draw(RenderTarget& target) {
			target.draw(this->gunSprite);
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

	dArr<Texture> *bodyTextures;
	dArr<Texture> *gunTextures;
	dArr<Texture> *bulletTextures;
	Sprite sprite;
	dArr<BossGun> guns;
	dArr<Bullet> bullets;

	int damageMax;
	int damageMin;

	int hpMax;
	int hp;
};

