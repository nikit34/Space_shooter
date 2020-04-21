#include "Player.h"

unsigned Player::players = 0;

enum controls { UP = 0, DOWN, LEFT, RIGHT, SHOOT };
enum weapons { LASER = 0, MISSILE01, MISSILE02 };

Player::Player(std::vector<Texture>& textures,
	dArr<Texture>& lWingTextures,
	dArr<Texture>& rWingTextures,
	dArr<Texture>& cPitTextures,
	dArr<Texture>& auraTextures,
	Vector2u windowBounds,
	int UP, int DOWN,
	int LEFT, int RIGHT,
	int SHOOT)
	:level(1),
	exp(0),
	hp(10),
	hpMax(10),
	statPoints(0), cooling(0),
	plating(0), wiring(0), power(0),
	damage(1),
	damageMax(2),
	score(0) {

	// Dt
	this->dtMultiplier = 60.f;

	// Stats
	this->expNext = 20 + static_cast<int>(
		(50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12));
	

	// Update positions
	this->playerCenter.x =
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y =
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;

	this->windowBounds = windowBounds;

	// Textures & Sprites
	this->lWingTextures = &lWingTextures;
	this->rWingTextures = &rWingTextures;
	this->cPitTextures = &cPitTextures;
	this->auraTextures = &auraTextures;

	this->sprite.setTexture(textures[0]);
	this->sprite.setScale(0.3f, 0.3f);
	this->sprite.setRotation(90);
	this->sprite.setPosition(40.f, (rand() % this->windowBounds.y) - this->sprite.getGlobalBounds().height);

	this->laserTexture = &textures[1];
	this->missile01Texture = &textures[2];

	this->mainGunSprite.setTexture(textures[3]);
	this->mainGunSprite.setOrigin(
		this->mainGunSprite.getGlobalBounds().width / 2,
		this->mainGunSprite.getGlobalBounds().height / 2
	);
	
	this->mainGunSprite.setRotation(270);
	this->mainGunSprite.setScale(0.5f, 0.5f);

	this->mainGunSprite.setPosition(
		this->playerCenter.x - 20.f,
		this->playerCenter.y
	);

	// Accessories
	this->lWing.setTexture((*this->lWingTextures)[0]);
	this->rWing.setTexture((*this->rWingTextures)[0]);
	this->cPit.setTexture((*this->cPitTextures)[0]);
	this->aura.setTexture((*this->auraTextures)[0]);

	// Init Accessories
	this->lWing.setOrigin(
		this->lWing.getGlobalBounds().width / 2,
		this->lWing.getGlobalBounds().height / 2
	);

	this->lWing.setPosition(this->playerCenter);
	this->lWing.setRotation(90.f);
	this->rWing.setOrigin(
		this->rWing.getGlobalBounds().width / 2,
		this->rWing.getGlobalBounds().height / 2
	);

	this->rWing.setPosition(this->playerCenter);
	this->rWing.setRotation(90.f);

	this->cPit.setOrigin(
		this->cPit.getGlobalBounds().width / 2,
		this->cPit.getGlobalBounds().height / 2
	);

	this->cPit.setPosition(this->playerCenter);
	this->cPit.setRotation(90.f);

	this->aura.setOrigin(
		this->aura.getGlobalBounds().width / 2,
		this->aura.getGlobalBounds().height / 2
	);

	this->aura.setPosition(this->playerCenter);
	this->aura.setRotation(90.f);

	// Timers
	this->shootTimerMax = 25.f;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 10.f;
	this->damageTimer = this->damageTimerMax;

	// Controls
	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;

	// Velocity & Acceleration
	this->maxVelocity = 25.f;
	this->acceleration = 0.8f;
	this->stabilizerForce = 0.4f;

	// Guns
	this->currentWeapon = LASER;
	// this->currentWeapon = MISSILE01;

	// Upgrades
	this->mainGunLevel = 0;        // mainGunLevel;
	this->dualMissiles01 = false;   // dualMissiles01;
	this->dualMissiles02 = false;  // dualMissiles02;

	// Add number to players for coop
	this->playerNr = Player::players;
	Player::players++;
}

Player::~Player() {}

int Player::getDamage() const {
	int damage = 0;
	switch (this->currentWeapon) {
	case LASER:
		damage = rand() % this->damageMax + this->damage; 
		break;
	case MISSILE01:
		damage = rand() % this->damageMax + this->damage;
		damage *= 2;
		break;
	case MISSILE02:
		damage = rand() % this->damageMax + this->damage;
		damage *= 4; 
		break;
	default:
		damage = rand() % this->damageMax + this->damage;
		break;
	}
	return damage;
}

bool Player::UpdateLeveling() {
	if (this->exp >= this->expNext) {
		this->level++;
		this->statPoints++;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>(
			(50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12));
		this->hp = hpMax;
		return true;
	}
	return false;
}

void Player::UpdateAccessories(const float &dt) {
	// Set the position of gun to follow player
	this->mainGunSprite.setPosition(
		this->mainGunSprite.getPosition().x,
		this->playerCenter.y
	);

	// Animate the main gun and correct it after firing
	if (this->mainGunSprite.getPosition().x < this->playerCenter.x - 20.f) {
		this->mainGunSprite.move(
			this->currentVelocity.x * dt * this->dtMultiplier + 2.f * dt * this->dtMultiplier, 0.f
		);
	}
	if (this->mainGunSprite.getPosition().x > this->playerCenter.x - 20.f) {
		this->mainGunSprite.setPosition(
			this->playerCenter.x - 20.f,
			this->playerCenter.y
		);
	}

	// Left wing
	this->lWing.setScale(0.3f, 0.3f);
	this->lWing.setPosition(
		playerCenter.x - 80.f,
		playerCenter.y
	);

	// Right wing
	this->rWing.setScale(0.3f, 0.3f);
	this->rWing.setPosition(
		playerCenter.x - 80.f,
		playerCenter.y
	);

	// Cockpit
	this->cPit.setScale(0.3f, 0.3f);
	this->cPit.setPosition(
		playerCenter.x - 90.f,
		playerCenter.y
	);
	
	// Aura
	this->aura.setScale(1.5f, 1.5f);
	this->aura.setPosition(
		playerCenter.x - 80.f,
		playerCenter.y
	);
}

void Player::Movement(const float& dt) {
	// UP
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP]))) {
		this->direction.x = 0.f;
		this->direction.y = -1.f;
		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration
			* dt * this->dtMultiplier;
	}
	// DOWN
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN]))) {
		this->direction.x = 0.f;
		this->direction.y = 1.f;
		if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
			this->currentVelocity.y += this->direction.y * this->acceleration 
			* dt * this->dtMultiplier;
	}
	// LEFT
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT]))) {
		this->direction.x = -1.f;
		this->direction.y = 0.f;
		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration
			* dt * this->dtMultiplier;
	}
	// RIGHT
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT]))) {
		this->direction.x = 1.f;
		this->direction.y = 0.f;
		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration
			* dt * this->dtMultiplier;
	}

	// Drag force
	if (this->currentVelocity.x > 0) {
		this->currentVelocity.x -= this->stabilizerForce * dt * this->dtMultiplier;
		if (this->currentVelocity.x < 0) this->currentVelocity.x = 0;
	}
	else if (this->currentVelocity.x < 0) {
		this->currentVelocity.x += this->stabilizerForce * dt * this->dtMultiplier;
		if (this->currentVelocity.x > 0) this->currentVelocity.x = 0;
	}
	if (this->currentVelocity.y > 0) {
		this->currentVelocity.y -= this->stabilizerForce * dt * this->dtMultiplier;
		if (this->currentVelocity.y < 0) this->currentVelocity.y = 0;
	}
	else if (this->currentVelocity.y < 0) {
		this->currentVelocity.y += this->stabilizerForce * dt * this->dtMultiplier;
		if (this->currentVelocity.y > 0) this->currentVelocity.y = 0;
	}

	// Final move
	this->sprite.move(this->currentVelocity.x * dt * this->dtMultiplier, 
		this->currentVelocity.y * dt * this->dtMultiplier);

	// Update positions
	this->playerCenter.x =
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y =
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;
}

void Player::Combat(const float& dt) {
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])) &&
		this->shootTimer >= this->shootTimerMax) {
		if (this->currentWeapon == LASER) {
			if (this->mainGunLevel == 0) {
				// Create bullet
				this->bullets.add(Bullet(
					laserTexture, Vector2f(this->playerCenter.x, this->playerCenter.y),
					Vector2f(0.5f, 0.5f), Vector2f(1.f, 0.f), 2.f, 70.f, 2.f));
			}
			else if (this->mainGunLevel == 1) {
			}
			else if (this->mainGunLevel == 2) {
			}
			// Animate gun
			this->mainGunSprite.move(-30.f, 0.f);
		}
		else if (this->currentWeapon == MISSILE01) {
			// Create bullet
			this->bullets.add(
				Bullet(missile01Texture,
					Vector2f(this->playerCenter.x, this->playerCenter.y - 10.f),
					Vector2f(0.5f, 0.2f), Vector2f(1.f, 0.f), 2.f, 45.f, 1.f));
			
			if (this->dualMissiles01) {
				this->bullets.add(
					Bullet(missile01Texture,
						Vector2f(this->playerCenter.x, this->playerCenter.y + 10.f),
						Vector2f(0.05f, 0.02f), Vector2f(1.f, 0.f), 2.f, 45.f, 1.f));
			}
		}
		else if (this->currentWeapon == MISSILE02) {
			if (this->dualMissiles02) {
			}
		}
		this->shootTimer = 0;  // Reset timer
	}
}

Bullet& Player::getBullet(unsigned index) {
	if (index < 0 || index > this->bullets.size())
		throw "OUT OF BOUNDS! PLAYER::GETBULLET";
	return this->bullets[index];
}

void Player::removeBullet(unsigned index) {
	if (index < 0 || index > this->bullets.size())
		throw "OUT OF BOUNDS! PLAYER::REMOVEBULLET";
	this->bullets.remove(index);
}

void Player::Update(Vector2u windowBounds, const float& dt) {
	// Update timers
	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer += 1 * dt * this->dtMultiplier;

	if (this->damageTimer < this->damageTimerMax) 
		this->damageTimer += 1 * dt * this->dtMultiplier;

	this->Movement(dt);
	this->UpdateAccessories(dt);
	this->Combat(dt);
}

void Player::Draw(RenderTarget& target) {
	target.draw(this->aura);
	for (size_t i = 0; i < this->bullets.size(); i++) {
		this->bullets[i].Draw(target);
	}

	target.draw(this->sprite);
	target.draw(this->lWing);
	target.draw(this->rWing);
	target.draw(this->cPit);
	target.draw(this->mainGunSprite);
}