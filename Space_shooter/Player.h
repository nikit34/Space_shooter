#pragma once

#include "Bullet.h"

class Player {
public:
	Player(std::vector<Texture>& textures,
		dArr<Texture>& lWingTextures,
		dArr<Texture>& rWingTextures, 
		dArr<Texture>& cPitTextures, 
		dArr<Texture>& auraTextures,
		int UP = 22, int DOWN = 18,
		int LEFT = 0, int RIGHT = 3,
		int SHOOT = 57
		);

	virtual ~Player();

	// Accessors
	Bullet& getBullet(unsigned index);
	void removeBullet(unsigned index);
	inline const int getBulletsSize() const { return this->bullets.size(); }
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline const String getHpAsString() const {
		return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }
	int getDamage() const;
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const int& getHp() const { return this->hp; }
	inline const int& getHpMax() const { return this->hpMax; }
	inline void takeDamage(int damage) { this->hp -= damage; }
	inline bool isAlive() const { return this->hp > 0; }
	inline const int& getPlayerNr() const { return this->playerNr; }
	inline const int& getLevel() const { return this->level; }
	inline const int& getExp() const { return this->exp; }
	inline const int& getExpNext() const { return this->expNext; }
	inline bool gainExp(int exp) { this->exp += exp; return this->UpdateLeveling(); }

	// Functions
	bool UpdateLeveling();
	void UpdateAccessories(const float& dt);
	void Combat(const float& dt);
	void Movement(const float& dt);
	void Update(Vector2u windowBounds, const float& dt);
	void Draw(RenderTarget& target);

	// Statics
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
	dArr<Bullet> bullets;
	Texture* laserTexture;
	Texture* missile01Texture;
	Texture* missile02Texture;

	dArr<Texture>* lWingTextures;
	dArr<Texture>* rWingTextures;
	dArr<Texture>* cPitTextures;
	dArr<Texture>* auraTextures;
	Sprite lWing;
	Sprite rWing;
	Sprite cPit;
	Sprite aura;

	int controls[5];
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	float stabilizerForce;

	int level;
	int exp;
	int expNext;
	int statPoints;

	int cooling; // endurance
	int plating; // vigor
	int power; // strength
	int wiring; // agility

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