#include "Enemy.h"

enum eTypes { MOVELEFT = 0, FOLLOW, FOLLOWFAST, FOLLOWSHOOT, FOLLOWFASTSHOOT };

Enemy::Enemy(Texture* texture, Vector2u windowBounds, Vector2f position,
	Vector2f direction, Vector2f scale, int type, int hpMax,
	int damageMax, int damageMin, int playerFollowNr) {
	
	this->dtMultiplier = 60.f;
	this->texture = texture;
	this->windowBounds = windowBounds;

	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(scale);
	this->sprite.setRotation(270);
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);
	this->sprite.setPosition(
		this->windowBounds.x,
		(rand() % this->windowBounds.y) - this->sprite.getGlobalBounds().height
	);

	this->damageTimerMax = 5.f;
	this->damageTimer = 0;

	this->direction = direction;

	this->type = type;

	this->hpMax = hpMax;
	this->hp = this->hpMax;

	this->damageMax = damageMax;
	this->damageMin = damageMin;

	this->playerFollowNr = playerFollowNr;
}

Enemy::~Enemy() {}

void Enemy::takeDamage(int damage) {
	this->hp -= damage;
	this->damageTimer = this->damageTimerMax;
	if (this->hp <= 0)
		this->hp = 0;
}

void Enemy::Update(const float& dt, Vector2f playerPosition) {
	Vector2f normalizedDir;
	switch (this->type) {
	case MOVELEFT:
		this->sprite.move(this->direction.x * 10.f * dt * this->dtMultiplier,
			this->direction.y * 10.f * dt * this->dtMultiplier);
		break;

	case FOLLOW:
		if (this->sprite.getPosition().x > playerPosition.x) {
			direction.x = playerPosition.x - this->sprite.getPosition().x;
			direction.y = playerPosition.y - this->sprite.getPosition().y;
		}
		
		normalizedDir = normalize(direction, vectorLength(direction));

		if (normalizedDir.y > 0.3)
			normalizedDir.y = 0.3;
		else if (normalizedDir.y < -0.3)
			normalizedDir.y = -0.3;
		if (normalizedDir.x > -0.7)
			normalizedDir.x = -0.7;

		this->sprite.setRotation(atan2(normalizedDir.y, normalizedDir.x) * 180 / 3.14 + 90);

		this->sprite.move(normalizedDir.x * 3.f * dt * this->dtMultiplier, normalizedDir.y * 3.f * dt * this->dtMultiplier);


	default:
		break;
	}
	if (this->damageTimer > 0) {
		this->damageTimer -= 0.5f * dt * dtMultiplier;
		this->sprite.setColor(Color::Red);
		this->sprite.move(2.f * this->damageTimer * dt * dtMultiplier, 0.f);
	}
	else {
		this->sprite.setColor(Color::White);
	}
}

void Enemy::Draw(RenderTarget& target) { target.draw(this->sprite); }