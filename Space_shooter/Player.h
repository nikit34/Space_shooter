#pragma once
#include"Bullet.h"

using namespace sf;


class Player
{
public:
	virtual ~Player();
	Player(Texture *texture,
		Texture *bulletTextur,
		int UP = 22, int DOWN = 18, 
		int LEFT = 0, int RIGHT = 3, 
		int SHOOT = 57);

	//Accessors
	inline std::vector<Bullet> &getBullets() { return this->bullets;  }
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }

	//Functions
	void Combat();
	void Movement();
	void Update(Vector2u windowBounds);
	void Draw(RenderTarget &target);

	static unsigned players;

private:
	unsigned playerNr;

	int shootTimer;
	int shootTimerMax;
	int damageTimer;
	int damageTimerMax;

	Sprite sprite;
	RectangleShape hitBox;
	Texture *texture;

	Texture *bulletTexture;
	std::vector<Bullet> bullets;

	int controls[5];

	int level;
	int exp;
	int expNext;

	int hp;
	int hpMax;

	int damage;
	int damageMax;

	int score;
};