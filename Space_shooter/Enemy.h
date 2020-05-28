#pragma once
#include"Wingman.h"
#include"Bullet.h"


class Enemy {
public:
	Enemy(
		View& view,
		bool randomPos,
		Vector2f position,
		Vector2f direction,
		int maxVelocity, 
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
	void update(const float &dt, Vector2f playerPosition);
	void draw(RenderTarget& target);

	// Regular functions
	float vectorLength(Vector2f v) { return sqrt(pow(v.x, 2) + pow(v.y, 2)); }

	Vector2f normalize(Vector2f v, float length) {
		if (length == 0)
			return Vector2f(0.f, 0.f);
		else
			return v / length;
	}

	// Static
	static dArr<Bullet> enemyBullets;

	enum eTypes { 
		MOVELEFT = 0, 
		FOLLOW, 
		MOVELEFTSHOOT,
		MOVELEFTSHOOTPLAYER,
		FOLLOWFAST, 
		FOLLOWSHOOT, 
		FOLLOWFASTSHOOT 
	};
	enum weapons { 
		REGULAR = 0, 
		MISSILE 
	};

	static dArr<Texture> textures;
	static int nrOfTextures;
	static void initTextures();
	static void initSounds();

	// Static sounds
	static SoundBuffer shootBuffer;
	static SoundBuffer hitArmorBuffer;
	static Sound shootSound;
	static Sound hitArmorSound;

	static unsigned nrOfTypes;

private:
	float dtMultiplier;

	Sprite sprite;
	Color color;
	Color damageColor;

	Vector2f moveDirection;
	Vector2f normalizedMoveDir;
	Vector2f lookDirection;
	Vector2f normalizedLookDir;
	int maxVelocity;

	float damageTimerMax;
	float damageTimer;

	int nrOfBullets;
	float shootTimerMax;
	float shootTimer;

	int type;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;

	int playerFollowNr;
};
