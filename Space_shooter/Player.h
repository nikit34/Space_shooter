#pragma once

#include"Bullet.h"

class Player {
public:
	Player(std::vector<Texture>& textures,
		dArr<Texture>& mainGunTextures,
		dArr<Texture>& lWingTextures,
		dArr<Texture>& rWingTextures, 
		dArr<Texture>& cPitTextures, 
		dArr<Texture>& auraTextures,
		int UP = Keyboard::W, 
		int DOWN = Keyboard::S,
		int LEFT = Keyboard::A,
		int RIGHT = Keyboard::D,
		int SHOOT = Keyboard::Space,
		int STATS = Keyboard::Tab,
		int CHANGE_LWING = Keyboard::Num1,
		int CHANGE_CPIT = Keyboard::Num2,
		int CHANGE_RWING = Keyboard::Num3,
		int CHANGE_AURA = Keyboard::Num4,
	);

	virtual ~Player();

	// Accessors
	Bullet& getBullet(unsigned index);
	void removeBullet(unsigned index);
	inline const int getBulletsSize() const { return this->bullets.size(); }
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline const String getHpAsString() const { return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }
	int getDamage() const;
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const int& getHp() const { return this->hp; }
	inline const int& getHpMax() const { return this->hpMax; }
	void takeDamage(int damage);
	inline bool isAlive() const { return this->hp > 0; }
	inline const int& getPlayerNr() const { return this->playerNr; }
	inline const int& getLevel() const { return this->level; }
	inline const int& getExp() const { return this->exp; }
	inline const int& getExpNext() const { return this->expNext; }
	inline bool gainExp(int exp) { this->exp += exp; return this->UpdateLeveling(); }
	inline void gainScore(int score) { this->score += score; }
	inline const int getScore() const { return this->score; }
	inline bool isDamageCooldown() { return this->damageTimer < this->damageTimerMax; }
	inline void gainHP(int hp) {
		this->hp += hp;
		if (this->hp > this->hpMax)
			this->hp = this->hpMax;
	}
	void setGunLevel(int gunLevel);
	inline void enablePiercingShot() { this->piercingShot = true; }
	inline void enableShield() { this->shield = true; }
	inline void enableDualMissiles01() { this->dualMissiles01 = true; }
	inline void enableDualMissiles02() { this->dualMissiles02 = true; }
	inline void upgradeHP() { this->hpAdded += 10; this->UpdateStats(); this->hp = this->hpMax; }
	inline bool getPiercingShot() const { return this->piercingShot; }
	inline const int& getGunLevel() const { return this->mainGunLevel; }
	inline void resetVelocity() { this->currentVelocity = Vector2f(0.f, 0.f); }
	inline void move(float x, float y) { this->sprite.move(x, y); this->mainGunSprite.move(x, y); }
	inline const Vector2f getNormDir() const { return this->normDir; }
	inline void addStatPoint() { this->statPoints++; }
	void addStatPointRandom();
	inline dArr<int>& getAcquiredUpgrades() { return this->upgradesAcquired; }

	// Functions
	void Reset();
	bool UpdateLeveling();
	void UpdateStats();
	void ChangeAccessories(const float& dt);
	void UpdateAccessories(const float& dt);
	void Combat(const float& dt);
	void Movement(Vector2u windowBounds, const float& dt);
	void Update(Vector2u windowBounds, const float& dt);
	void Draw(RenderTarget& target);

	// Statics
	static unsigned players;

	// Regular functions
	float vectorLength(Vector2f v) {
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}

	Vector2f normalize(Vector2f v, float length) {
		if (length == 0)
			return Vector2f(0.f, 0.f);
		else
			return v / length;
	}

private:
	float dtMultiplier;
	float keyTimeMax;
	float keyTime;

	unsigned playerNr;

	Vector2f playerCenter;
	Vector2u windowBounds;

	float shootTimer;
	float shootTimerMax;
	float damageTimer;
	float damageTimerMax;

	Sprite sprite;
	RectangleShape hitBox;

	// Accessories
	Sprite mainGunSprite;
	dArr<Bullet> bullets;
	dArr<Texture>* mainGunTextures;
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

	int lWingSelect;
	int rWingSelect;
	int cPitSelect;
	int auraSelect;

	int controls[5];
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	float stabilizerForce;
	Vector2f normDir;

	int level;
	int exp;
	int expNext;
	int statPoints;

	int cooling; // endurance - выносливость
	int plating; // vigor - сила
	int power; // strength - прочность
	int wiring; // agility - проворство

	int hp;
	int hpMax;
	int hpAdded;

	int damage;
	int damageMax;

	int score;

	int currentWeapon;

	// Upgrades
	dArr<int> upgradesAcquired;
	int mainGunLevel;
	bool piercingShot;
	bool shield;
	bool dualMissiles01;
	bool dualMissiles02;
};