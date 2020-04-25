#pragma once

#include "Bullet.h"

class Enemy {
public:
	Enemy(dArr<Texture> &textures, 
		Vector2u windowBounds, 
		Vector2f position,
		Vector2f direction, 
		Vector2f scale, 
		int type, 
		int scalar, 
		int playerFollowNr
	);

	virtual ~Enemy();

	// Accessors
	inline const int getDamage() const { return rand() % this->damageMax + this->damageMin; }
	inline const int getHp() const { return this->hp; }
	inline const int getHpMax() const { return this->hpMax; }
	inline const bool isDead() const { return this->hp <= 0; }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition() const { return this->sprite.getPosition(); }
	inline const int& getPlayerFollowNr() const { return this->playerFollowNr; }

	// Functions
	void collision();
	void takeDamage(int damage);
	void Update(const float &dt, Vector2f playerPosition);
	void Draw(RenderTarget& target);

	float vectorLength(Vector2f v) { return sqrt(pow(v.x, 2) + pow(v.y, 2)); }

	Vector2f normalize(Vector2f v, float length) {
		if (length == 0)
			return Vector2f(0.f, 0.f);
		else
			return v / length;
	}

private:
	float dtMultiplier;

	dArr<Texture>* textures;
	Sprite sprite;
	Vector2u windowBounds;
	Vector2f moveDirection;
	Vector2f normalizedMoveDir;
	Vector2f lookDirection;
	Vector2f normalizedLookDir;
	float maxVelocity;


	float damageTimerMax;
	float damageTimer;

	int type;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;

	int playerFollowNr;
};
