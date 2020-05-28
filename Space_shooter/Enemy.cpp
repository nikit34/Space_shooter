#include"Enemy.h"


unsigned Enemy::nrOfTypes = 4;

// Static define
dArr<Bullet> Enemy::enemyBullets;
dArr<Texture> Enemy::textures;
int Enemy::nrOfTextures;

void Enemy::initTextures() {
	Texture temp;
	temp.loadFromFile("Textures/enemyMoveLeft.png");
	Enemy::textures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyFollow.png");
	Enemy::textures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyMoveLeftShoot.png");
	Enemy::textures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyMoveLeftShootPlayer.png");
	Enemy::textures.add(Texture(temp));

	Enemy::nrOfTextures = Enemy::textures.size();
}

// Sounds
SoundBuffer Enemy::shootBuffer;
SoundBuffer Enemy::hitArmorBuffer;
Sound Enemy::shootSound;
Sound Enemy::hitArmorSound;

void Enemy::initSounds() {
	Enemy::shootBuffer.loadFromFile("Sounds/shoot_enemy.wav");
	Enemy::shootSound.setBuffer(Enemy::shootBuffer);
	Enemy::shootSound.setVolume(70.f);

	// Hit armor
	Enemy::hitArmorBuffer.loadFromFile("Sounds/hitArmorEnemy.wav");
	Enemy::hitArmorSound.setBuffer(Enemy::hitArmorBuffer);
	Enemy::hitArmorSound.setVolume(100.f);
}

Enemy::Enemy(
	View& view,
	bool randomPos,
	Vector2f position,
	Vector2f moveDirection,
	int maxVelocity,
	int type, 
	int scalar, 
	int playerFollowNr
) {
	this->dtMultiplier = 60.f;

	if (type >= Enemy::nrOfTextures) {
		type = Enemy::nrOfTextures - 1;
	}
	else if (type < 0) {
		type = 0;
	}
	this->moveDirection = moveDirection;
	this->type = type;
	this->sprite.setTexture(Enemy::textures[this->type]);
	this->sprite.setRotation(270);
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2);

	this->color = Color::White;
	this->damageColor = Color::Red;

	this->damageTimerMax = 4.f;
	this->damageTimer = 0;
	this->nrOfBullets = 0;
	this->shootTimerMax = 50.f;
	this->shootTimer = this->shootTimerMax;
	
	switch (this->type)
	{
	case MOVELEFT:
		this->sprite.setScale(Vector2f(0.4f, 0.4f));
		this->hpMax = (rand() % 5 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 3 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		if (maxVelocity < 0.f)
			this->maxVelocity = rand() % 20 + 5;
		else
			this->maxVelocity = maxVelocity;
		break;
	case FOLLOW:
		this->sprite.setScale(Vector2f(0.3f, 0.3f));
		this->hpMax = (rand() % 3 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		if (maxVelocity < 0.f)
			this->maxVelocity = rand() % 6 + 3;
		else
			this->maxVelocity = maxVelocity;
		break;
	case MOVELEFTSHOOT:
		this->sprite.setScale(Vector2f(0.35f, 0.35f));
		this->hpMax = (rand() % 5 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 5 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		this->nrOfBullets = 3;
		this->shootTimerMax = 8.f;
		this->shootTimer = 0.f;
		if (maxVelocity < 0.f)
			this->maxVelocity = rand() % 10 + 5;
		else
			this->maxVelocity = maxVelocity;
		break;
	case MOVELEFTSHOOTPLAYER:
		this->sprite.setScale(Vector2f(0.35f, 0.35f));
		this->hpMax = (rand() % 3 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		this->shootTimerMax = 50.f;
		this->shootTimer = 0.f;
		if (maxVelocity < 0.f)
			this->maxVelocity = rand() % 10 + 3;
		else
			this->maxVelocity = maxVelocity;
		break;
	default:
		this->hpMax = (rand() % 2 + 1) * scalar;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scalar;
		this->damageMin = (rand() % 1 + 1) * scalar;
		if (maxVelocity < 0.f)
			this->maxVelocity = rand() % 15 + 5;
		else
			this->maxVelocity = maxVelocity;
		break;
	}

	this->hpMax = hpMax;
	this->hp = this->hpMax;
	this->damageMax = damageMax;
	this->damageMin = damageMin;

	if (randomPos) {
		this->sprite.setPosition((view.getCenter().x + view.getSize().x / 2),
			(rand() % static_cast<int>(view.getCenter().y + view.getSize().y) + static_cast<int>(view.getCenter().y - view.getSize().y)));
	}
	else {
		this->sprite.setPosition(position);
	}
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

void Enemy::update(const float& dt, Vector2f playerPosition) {
	switch (this->type) {
	case MOVELEFT:
		this->sprite.move(
			this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier);
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
			this->normalizedMoveDir.y * this->maxVelocity * dt * this->dtMultiplier);
		break;

	case MOVELEFTSHOOT:
		this->sprite.move(
			this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier);
		this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));

		// Shoot
		if (this->shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * this->dtMultiplier;

		if (this->shootTimer >= this->shootTimerMax && this->nrOfBullets > 0) {
			Enemy::enemyBullets.add(Bullet(
				Bullet::BULLET_CIRCULAR_RED,
				this->sprite.getPosition(),
				Vector2f(0.75f, 0.75f),
				this->normalizedMoveDir,
				0.f,
				this->maxVelocity * 5.f,
				5.f,
				this->getDamage()
			));
			Enemy::shootSound.play();
			this->shootTimer = 0.f;
			this->nrOfBullets--;
		}
		break;

	case MOVELEFTSHOOTPLAYER:
		this->sprite.move(
			this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier);
		this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));

		// Shoot
		if (this->shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * this->dtMultiplier;

		this->lookDirection.x = playerPosition.x - this->sprite.getPosition().x;
		this->lookDirection.y = playerPosition.y - this->sprite.getPosition().y;
		this->normalizedLookDir = normalize(this->lookDirection, vectorLength(this->lookDirection));
		this->sprite.setRotation(atan2(this->normalizedLookDir.y, this->normalizedLookDir.x) * 180 / 3.14 + 90);

		if (this->shootTimer >= this->shootTimerMax) {
			Enemy::enemyBullets.add(Bullet(
				Bullet::BULLET_CIRCULAR_RED,
				this->sprite.getPosition(),
				Vector2f(0.75f, 0.75f),
				this->normalizedLookDir,
				1.5f,
				7.f,
				0.5f,
				this->getDamage()
			));
			Enemy::shootSound.play();
			this->shootTimer = 0.f;
		}
		break;

	default:
		break;
	}

	// Damaged
	if (this->damageTimer > 0.f) {
		this->damageTimer -= 0.5f * dt * dtMultiplier;
		this->sprite.setColor(damageColor);
		this->sprite.move(
			2.f * -this->normalizedMoveDir.x * this->damageTimer * dt * dtMultiplier,
			2.f * -this->normalizedMoveDir.y * this->damageTimer * dt * dtMultiplier);
	}
	else {
		this->sprite.setColor(color);
	}
}

void Enemy::draw(RenderTarget& target) { 
	target.draw(this->sprite); 
}