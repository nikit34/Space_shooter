#include "Enemy.h"

enum eTypes { MOVELEFT = 0, FOLLOW, FOLLOWFAST, FOLLOWSHOOT, FOLLOWFASTSHOOT };

Enemy::Enemy(dArr<Texture>& textures, Vector2u windowBounds, Vector2f position,
	Vector2f direction, Vector2f scale, int type, int scalar, int playerFollowNr) {
	
	this->dtMultiplier = 60.f;
	this->textures = &textures;
	this->windowBounds = windowBounds;

	this->type = type;

	this->sprite.setTexture((*this->textures)[this->type]);
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

	this->maxVelocity = maxVelocity;

	this->damageTimerMax = 4.f;
	this->damageTimer = 0;

	this->direction = direction;

	switch (this->type)
	{
	case MOVELEFT:
		this->hpMax = (rand() % 5 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 3 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		this->maxVelocity = rand() % 20 + 5;
		break;
	case FOLLOW:
		this->hpMax = (rand() % 3 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		this->maxVelocity = 9;
		break;
	default:
		this->maxVelocity = 15;
		break;
	}

	this->hpMax = hpMax;
	this->hp = this->hpMax;

	this->damageMax = damageMax;
	this->damageMin = damageMin;

	this->playerFollowNr = playerFollowNr;
}

Enemy::~Enemy() {}

void Enemy::collision() {
	this->damageTimer = this->damageTimerMax;
}

void Enemy::takeDamage(int damage) {
	this->hp -= damage;
	this->damageTimer = this->damageTimerMax;
	if (this->hp <= 0)
		this->hp = 0;
}

void Enemy::Update(const float& dt, Vector2f playerPosition) {
	switch (this->type) {
	case MOVELEFT:
		this->sprite.move(this->direction.x * this->maxVelocity * dt * this->dtMultiplier,
			this->direction.y * this->maxVelocity * dt * this->dtMultiplier);

		this->normalizedDir = normalize(this->direction, vectorLength(this->direction));
		break;

	case FOLLOW:
		if (this->sprite.getPosition().x > playerPosition.x) {
			this->direction.x = playerPosition.x - this->sprite.getPosition().x;
			this->direction.y = playerPosition.y - this->sprite.getPosition().y;
		}
		
		this->normalizedDir = normalize(this->direction, vectorLength(this->direction));

		if (this->normalizedDir.y > 0.3)
			this->normalizedDir.y = 0.3;
		else if (this->normalizedDir.y < -0.3)
			this->normalizedDir.y = -0.3;
		if (this->normalizedDir.x > -0.7)
			this->normalizedDir.x = -0.7;

		this->sprite.setRotation(atan2(this->normalizedDir.y, this->normalizedDir.x) * 180 / 3.14 + 90);

		this->sprite.move(
			this->normalizedDir.x * this->maxVelocity * dt * this->dtMultiplier, 
			this->normalizedDir.y * this->maxVelocity * dt * this->dtMultiplier
		);
		break;

	default:
		break;
	}

	// Damaged
	if (this->damageTimer > 0.f) {
		this->damageTimer -= 0.5f * dt * dtMultiplier;
		this->sprite.setColor(Color::Red);
		this->sprite.move(
			2.f * -this->normalizedDir.x * this->damageTimer * dt * dtMultiplier, 
			2.f * -this->normalizedDir.y * this->damageTimer * dt * dtMultiplier
		);
	}
	else {
		this->sprite.setColor(Color::White);
	}
}

void Enemy::Draw(RenderTarget& target) { 
	target.draw(this->sprite); 
}