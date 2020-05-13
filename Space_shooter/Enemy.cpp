#include"Enemy.h"

dArr<Bullet> Enemy::enemyBullets;

enum eTypes { MOVELEFT = 0, FOLLOW, MOVELEFTSHOOT, FOLLOWFAST, FOLLOWSHOOT, FOLLOWFASTSHOOT };
enum bulletTypes { REGULAR = 0, MISSILE };

Enemy::Enemy(
	dArr<Texture>& textures, 
	dArr<Texture>& bulletTextures,
	Vector2u windowBounds, 
	Vector2f position,
	Vector2f moveDirection,
	int type, 
	int scalar, 
	int playerFollowNr
) {
	this->dtMultiplier = 60.f;
	this->windowBounds = windowBounds;

	this->textures = &textures;
	this->bulletTextures = &bulletTextures;
	this->type = type;

	this->sprite.setTexture((*this->textures)[this->type]);
	this->sprite.setRotation(270);
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);

	this->damageTimerMax = 4.f;
	this->damageTimer = 0;

	this->shootTimerMax = 50.f;
	this->shootTimer = this->shootTimerMax;

	this->moveDirection = moveDirection;

	switch (this->type)
	{
	case MOVELEFT:
		this->sprite.setScale(Vector2f(0.4f, 0.4f));
		this->hpMax = (rand() % 5 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 3 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		this->maxVelocity = rand() % 20 + 5;
		break;
	case FOLLOW:
		this->sprite.setScale(Vector2f(0.3f, 0.3f));
		this->hpMax = (rand() % 3 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		this->maxVelocity = 9;
		break;
	case MOVELEFTSHOOT:
		this->sprite.setScale(Vector2f(0.35f, 0.35f));
		this->hpMax = (rand() % 3 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		this->maxVelocity = 13;
		this->shootTimerMax = 15.f;
		this->shootTimer = 0.f;
		break;
	default:
		this->hpMax = (rand() % 2 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		this->maxVelocity = 20;
		break;
	}

	this->hpMax = hpMax;
	this->hp = this->hpMax;

	this->damageMax = damageMax;
	this->damageMin = damageMin;

	this->playerFollowNr = playerFollowNr;

	this->sprite.setPosition(
		this->windowBounds.x,
		(rand() % this->windowBounds.y) - this->sprite.getGlobalBounds().height
	);
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

void Enemy::update(const float& dt, Vector2f playerPosition) {
	switch (this->type) {
	case MOVELEFT:
		this->sprite.move(
			this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier
		);

		this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));
		break;

	case FOLLOW:
		if (this->sprite.getPosition().x > playerPosition.x) {
			this->moveDirection.x = playerPosition.x - this->sprite.getPosition().x;
			this->moveDirection.y = playerPosition.y - this->sprite.getPosition().y;
		}
		
		this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));

		if (this->normalizedMoveDir.y > 0.3)
			this->normalizedMoveDir.y = 0.3;
		else if (this->normalizedMoveDir.y < -0.3)
			this->normalizedMoveDir.y = -0.3;
		if (this->normalizedMoveDir.x > -0.7)
			this->normalizedMoveDir.x = -0.7;

		this->sprite.setRotation(atan2(this->normalizedMoveDir.y, this->normalizedMoveDir.x) * 180 / 3.14 + 90);

		this->sprite.move(
			this->normalizedMoveDir.x * this->maxVelocity * dt * this->dtMultiplier,
			this->normalizedMoveDir.y * this->maxVelocity * dt * this->dtMultiplier
		);
		break;

	case MOVELEFTSHOOT:
		this->shootTimerMax = 50.f;
		if (this->shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * this->dtMultiplier;

		this->lookDirection.x = playerPosition.x - this->sprite.getPosition().x;
		this->lookDirection.y = playerPosition.y - this->sprite.getPosition().y;
		
		this->normalizedLookDir = normalize(this->lookDirection, vectorLength(this->lookDirection));

		this->sprite.setRotation(atan2(this->normalizedLookDir.y, this->normalizedLookDir.x) * 180 / 3.14 + 90);

		this->sprite.move(this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier);

		this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));

		// Shoot
		if (this->shootTimer >= this->shootTimerMax) {
			Enemy::enemyBullets.add(Bullet(
				&(*this->bulletTextures)[REGULAR],
				this->sprite.getPosition(),
				Vector2f(0.7f, 0.7f),
				this->normalizedLookDir,
				1.5f,
				7.f,
				0.5f
			));
			this->shootTimer = 0.f;
		}
		break;

	default:
		break;
	}

	// Damaged
	if (this->damageTimer > 0.f) {
		this->damageTimer -= 0.5f * dt * dtMultiplier;
		this->sprite.setColor(Color::Red);
		this->sprite.move(
			2.f * -this->normalizedMoveDir.x * this->damageTimer * dt * dtMultiplier,
			2.f * -this->normalizedMoveDir.y * this->damageTimer * dt * dtMultiplier
		);
	}
	else {
		this->sprite.setColor(Color::White);
	}
}

void Enemy::draw(RenderTarget& target) { 
	target.draw(this->sprite); 
}