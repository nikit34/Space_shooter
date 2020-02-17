#pragma once

#include"Bullet.h"


class Enemy
{
public:
	Enemy(Texture *texture,
		Vector2f position, Vector2f direction,
		Vector2f scale, int type,
		int hpMax, int damageMin, int damageMax);

	virtual ~Enemy();

	//Accessors
	inline const int getDamage() const 
	{ 
		return rand() % this->damageMax + this->damageMin;
	}
	inline const int getHp() const { return this->hp; }
	inline const int getHpMax() const { return this->hpMax; }
	inline const bool isDead() const { return this->hp <= 0; }
	inline const FloatRect& getGlobalBound() const { return this->sprite.getGlobalBounds(); }
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }

	//Functions
	void takeDamage(int damage);
	void Update();
	void Draw(RenderTarget &target);

private:
	Texture	*texture;
	Sprite sprite;

	int type;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
};

