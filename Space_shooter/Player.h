#pragma once

#include "Bullet.h"

class Player {
public:
	virtual ~Player();
	Player(std::vector<Texture>& textures, int UP = 22, int DOWN = 18,
		int LEFT = 0, int RIGHT = 3, int SHOOT = 57);

	// Accessors
	inline std::vector<Bullet>& getBullets() { return this->bullets; }
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline const String getHpAsString() const {
		return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }
	inline const int getDamage() const { return rand() % this->damageMax + this->damage; }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const int& getHp() const { return this->hp; }
	inline const int& getHpMax() const { return this->hpMax; }
	inline void takeDamage(int damage) { this->hp -= damage; }
	inline bool isAlive() const { return this->hp > 0; }
	inline const int& getPlayerNr() const { return this->playerNr; }
	inline const int& getLevel() const { return this->level; }
	inline const int& getExp() const { return this->exp; }
	inline const int& getExpNext() const { return this->expNext; }

	// Functions
	void UpdateAccessories(const float& dt);
	void Combat(const float& dt);
	void Movement(const float& dt);
	void Update(Vector2u windowBounds, const float& dt);
	void Draw(RenderTarget& target);

	static unsigned players;

private:
	float dtMultiplier;

	unsigned playerNr;

	Vector2f playerCenter;

	float shootTimer;
	float shootTimerMax;
	float damageTimer;
	float damageTimerMax;

	Sprite sprite;
	RectangleShape hitBox;

	// Accessories
	Sprite mainGunSprite;
	std::vector<Bullet> bullets;
	Texture* laserTexture;
	Texture* missile01Texture;
	Texture* missile02Texture;

	int controls[5];
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	float stabilizerForce;

	int level;
	int exp;
	int expNext;

	int hp;
	int hpMax;

	int damage;
	int damageMax;

	int score;

	// Upgrades
	int currentWeapon;

	int mainGunLevel;
	bool dualMissiles01;
	bool dualMissiles02;
};