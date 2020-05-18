#include "Player.h"

unsigned Player::players = 0;

// Textures
dArr<Texture> Player::playerBodyTextures;
dArr<Texture> Player::playerBulletTextures;
dArr<Texture> Player::playerMainGunTextures;
dArr<Texture> Player::playerShieldTextures;
dArr<Texture> Player::lWingTextures;
dArr<Texture> Player::rWingTextures;
dArr<Texture> Player::cPitTextures;
dArr<Texture> Player::auraTextures;

Player::Player(
	int UP,
	int DOWN,
	int LEFT,
	int RIGHT,
	int SHOOT,
	int SHIELD,
	int STATS,
	int CHANGE_LWING,
	int CHANGE_CPIT,
	int CHANGE_RWING,
	int CHANGE_AURA)
	:level(1), exp(0),
	hp(10), hpMax(10), hpAdded(10),
	statPoints(0), 
	cooling(0), plating(0), wiring(0), power(0),
	damage(1), damageMax(2),
	score(0) {

	// Dt
	this->dtMultiplier = 60.f;

	// KeyTime
	this->keyTimeMax = 8.f;
	this->keyTime = this->keyTimeMax;
	
	// Stats
	this->expNext = 20 + static_cast<int>(
		(50 / 3) * ((pow(level, 3) - 
		6 * pow(level, 2)) + 
		17 * level - 12));
	
	// Update positions
	this->playerCenter.x =
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y =
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;

	// Textures & Sprites
	this->sprite.setTexture(Player::playerBodyTextures[0]);
	this->sprite.setScale(0.3f, 0.3f);
	this->sprite.setRotation(90);
	this->sprite.setPosition(40.f, (rand() % 800) - this->sprite.getGlobalBounds().height);
	this->sprite.setColor(Color(10, 10, 10, 255));

	this->mainGunSprite.setTexture(Player::playerMainGunTextures[0]);
	this->mainGunSprite.setOrigin(
		this->mainGunSprite.getGlobalBounds().width / 2,
		this->mainGunSprite.getGlobalBounds().height / 2);
	this->mainGunSprite.setRotation(270);
	this->mainGunSprite.setScale(0.5f, 0.5f);
	this->mainGunSprite.setPosition(
		this->playerCenter.x,
		this->playerCenter.y);

	this->deflectorShield.setTexture(Player::playerShieldTextures[0]);
	this->deflectorShield.setOrigin(
		this->deflectorShield.getGlobalBounds().width / 2,
		this->deflectorShield.getGlobalBounds().height / 2);

	// Accessories

	// Selectors
	this->lWingSelect = 0;
	this->rWingSelect = 0;
	this->cPitSelect = 0;
	this->auraSelect = 0;

	// Accessory textures
	this->lWing.setTexture(Player::lWingTextures[this->lWingSelect]);
	this->rWing.setTexture(Player::rWingTextures[this->rWingSelect]);
	this->cPit.setTexture(Player::cPitTextures[this->cPitSelect]);
	this->aura.setTexture(Player::auraTextures[this->auraSelect]);

	// Init Accessories
	float accScale = 0.3f;
	this->lWing.setOrigin(
		this->lWing.getGlobalBounds().width / 2,
		this->lWing.getGlobalBounds().height / 2);
	this->lWing.setScale(accScale, accScale);
	this->lWing.setPosition(this->playerCenter);
	this->lWing.setRotation(90.f);

	this->rWing.setOrigin(
		this->rWing.getGlobalBounds().width / 2,
		this->rWing.getGlobalBounds().height / 2);
	this->rWing.setScale(accScale, accScale);
	this->rWing.setPosition(this->playerCenter);
	this->rWing.setRotation(90.f);

	this->cPit.setOrigin(
		this->cPit.getGlobalBounds().width / 2,
		this->cPit.getGlobalBounds().height / 2);
	this->cPit.setScale(accScale, accScale);
	this->cPit.setPosition(this->playerCenter);
	this->cPit.setRotation(90.f);

	this->aura.setOrigin(
		this->aura.getGlobalBounds().width / 2,
		this->aura.getGlobalBounds().height / 2);
	this->aura.setScale(accScale, accScale);
	this->aura.setPosition(this->playerCenter);
	this->aura.setRotation(90.f);

	// Timers
	this->shootTimerMax = 20.f;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 40.f;
	this->damageTimer = this->damageTimerMax;
	this->shieldTimerMax = 50.f + this->cooling + (this->wiring / 2);
	this->shieldTimer = this->shieldTimerMax;
	this->shieldRechargeTimerMax = 300.f;
	this->shieldRechargeTimer = this->shieldRechargeTimerMax;
	this->powerupTimerMax = 300.f;
	this->powerupTimer = 0.f;


	// Controls
	this->controls.add(int(UP));
	this->controls.add(int(DOWN));
	this->controls.add(int(LEFT));
	this->controls.add(int(RIGHT));
	this->controls.add(int(SHOOT));
	this->controls.add(int(SHIELD));
	this->controls.add(int(STATS));
	this->controls.add(int(CHANGE_LWING));
	this->controls.add(int(CHANGE_CPIT));
	this->controls.add(int(CHANGE_RWING));
	this->controls.add(int(CHANGE_AURA));

	// Velocity & Acceleration
	this->maxVelocity = 25.f;
	this->acceleration = 0.8f;
	this->stabilizerForce = 0.4f;

	// Guns
	this->currentWeapon = LASER;
	// this->currentWeapon = MISSILE01;

	// Shileds
	this->shielding = false;

	// Upgrades
	this->mainGunLevel = 0;
	this->piercingShot = false;
	this->shield = false;
	this->dualMissiles01 = false;
	this->dualMissiles02 = false;

	// Powerups
	this->powerupRF = false;
	this->powerupXP = false;

	this->setGunLevel(0);

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

void Player::takeDamage(int damage) {
	this->hp -= damage;

	this->damageTimer = 0;

	this->currentVelocity.x += -this->normDir.x * 10.f;		
	this->currentVelocity.y += -this->normDir.y * 10.f;
}

bool Player::updateLeveling() {
	if (this->exp >= this->expNext) {
		this->level++;
		this->statPoints++;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>(
			(50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12));

		this->wiring++;
		this->cooling++;
		this->plating++;
		this->power++;

		this->updateStats();

		this->hp = hpMax;

		return true;
	}
	return false;
}

void Player::updateStats()		 {
	this->hpMax = this->hpAdded + this->plating * 5;
	this->damageMax = 2 + this->power * 2;
	this->damage = 1 + this->power;
	this->shieldTimerMax = 50.f + this->cooling + (this->wiring / 2);
}

void Player::changeAccessories(const float& dt) {
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;

	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[CHANGE_LWING])) && this->keyTime >= this->keyTimeMax) {
		if (lWingSelect < Player::lWingTextures.size() - 1)
			lWingSelect++;
		else
			lWingSelect = 0;

		this->lWing.setTexture(Player::lWingTextures[lWingSelect]);
		this->keyTime = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[CHANGE_RWING])) && this->keyTime >= this->keyTimeMax) {
		if (rWingSelect < Player::rWingTextures.size() - 1)
			rWingSelect++;
		else 
			rWingSelect = 0;

		this->rWing.setTexture(Player::rWingTextures[rWingSelect]);
		this->keyTime = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[CHANGE_CPIT])) && this->keyTime >= this->keyTimeMax) {
		if (cPitSelect < Player::cPitTextures.size() - 1)
			cPitSelect++;
		else 
			cPitSelect = 0;

		this->cPit.setTexture(Player::cPitTextures[cPitSelect]);
		this->keyTime = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[CHANGE_AURA])) && this->keyTime >= this->keyTimeMax) {
		if (auraSelect < Player::auraTextures.size() - 1)
			auraSelect++;
		else
			auraSelect = 0;

		this->aura.setTexture(Player::auraTextures[auraSelect]);
		this->keyTime = 0;
	}
}

void Player::updateAccessories(const float &dt) {
	// Set the position of gun to follow player
	this->mainGunSprite.setPosition(
		this->mainGunSprite.getPosition().x,
		this->playerCenter.y);

	// Animate the main gun and correct it after firing
	if (this->mainGunSprite.getPosition().x < this->playerCenter.x - 40.f) {
		this->mainGunSprite.move(
			this->currentVelocity.x * dt * this->dtMultiplier + 4.f * dt * this->dtMultiplier, 
			0.f);
	}
	if (this->mainGunSprite.getPosition().x > this->playerCenter.x - 40.f) {
		this->mainGunSprite.setPosition(
			this->playerCenter.x - 40.f,
			this->playerCenter.y);
	}

	// Set the position of the shield to follow player
	this->deflectorShield.setScale(1.f, 1.f);
	this->deflectorShield.setPosition(
		playerCenter.x - this->sprite.getGlobalBounds().width,
		playerCenter.y - 10.f);

	// Left wing
	this->lWing.setScale(0.3f, 0.3f);
	this->lWing.setPosition(
		playerCenter.x - 80.f - abs(this->currentVelocity.x),
		playerCenter.y - abs(this->currentVelocity.x / 2 + this->currentVelocity.y / 2));

	// Right wing
	this->rWing.setScale(0.3f, 0.3f);
	this->rWing.setPosition(
		playerCenter.x - 80.f - abs(this->currentVelocity.x),
		playerCenter.y + abs(this->currentVelocity.x / 2 + this->currentVelocity.y / 2));

	// Cockpit
	this->cPit.setScale(0.3f, 0.3f);
	this->cPit.setPosition(
		playerCenter.x - 90.f + this->currentVelocity.x,
		playerCenter.y);
	
	// Aura
	this->aura.setScale(0.2f, 0.2f);
	this->aura.setPosition(
		playerCenter.x - 90.f,
		playerCenter.y - 35.f);
	this->aura.rotate(1.2f * dt * this->dtMultiplier);
}

void Player::updatePowerups() {
	if (this->powerupTimer <= 0.f) {
		this->powerupRF = false;
		this->powerupXP = false;
	}
}

void Player::movement(View& view, const float& dt) {
	// Update normalized direction
	this->normDir = normalize(this->currentVelocity, vectorLength(this->currentVelocity));

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
		if (this->currentVelocity.x < 0) 
			this->currentVelocity.x = 0;
	}
	if (this->currentVelocity.x < 0) {
		this->currentVelocity.x += this->stabilizerForce * dt * this->dtMultiplier;
		if (this->currentVelocity.x > 0) 
			this->currentVelocity.x = 0;
	}
	if (this->currentVelocity.y > 0) {
		this->currentVelocity.y -= this->stabilizerForce * dt * this->dtMultiplier;
		if (this->currentVelocity.y < 0) 
			this->currentVelocity.y = 0;
	}
	if (this->currentVelocity.y < 0) {
		this->currentVelocity.y += this->stabilizerForce * dt * this->dtMultiplier;
		if (this->currentVelocity.y > 0) 
			this->currentVelocity.y = 0;
	}

	// Final move
	this->sprite.move(
		this->currentVelocity.x * dt * this->dtMultiplier, 
		this->currentVelocity.y * dt * this->dtMultiplier
	);

	// Update positions
	this->playerCenter.x =
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y =
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;

	// Window collision
	// Left
	if (this->getPosition().x <= view.getCenter().x - view.getSize().x / 2) {
		this->sprite.setPosition(view.getCenter().x - view.getSize().x / 2 + 10.f, this->sprite.getPosition().y);
		this->currentVelocity.x = 0.f;
	}
	// Right
	else if (this->getPosition().x + this->getBounds().width >= view.getCenter().x + view.getSize().x / 2) {
		this->sprite.setPosition(view.getCenter().x + view.getSize().x / 2 - this->getBounds().width, this->sprite.getPosition().y);
		this->currentVelocity.x = 0.f;
	}
	// Top
	if (this->getPosition().y <= view.getCenter().y - view.getSize().y / 2) {
		this->sprite.setPosition(this->sprite.getPosition().x, view.getCenter().y - view.getSize().y / 2);
		this->currentVelocity.y = 0.f;
	}
	// Bottom
	else if (this->getPosition().y + this->getBounds().height >= view.getCenter().y + view.getSize().y / 2) {
		this->sprite.setPosition(this->sprite.getPosition().x, view.getCenter().y + view.getSize().y / 2 - this->getBounds().height);
		this->currentVelocity.y = 0.f;
	}
}

void Player::combat(const float& dt) {
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])) &&
		this->shootTimer >= this->shootTimerMax) {
		if (this->currentWeapon == LASER) {
			if (this->mainGunLevel == 0) {
				// Create bullet
				this->bullets.add(Bullet(
					&Player::playerBulletTextures[LASER], 
					Vector2f(this->playerCenter.x, this->playerCenter.y),
					Vector2f(0.5f, 0.5f), 
					Vector2f(1.f, 0.f), 
					2.f, 
					70.f, 
					2.f,
					this->getDamage()
				));
			}
			else if (this->mainGunLevel == 1) {
				this->bullets.add(Bullet(
					&Player::playerBulletTextures[LASER],
					Vector2f(this->playerCenter.x, this->playerCenter.y - 10.f),
					Vector2f(0.5f, 0.5f),
					Vector2f(1.f, 0.f),
					2.f,
					70.f,
					2.f,
					this->getDamage()
				));
				this->bullets.add(Bullet(
					&Player::playerBulletTextures[LASER],
					Vector2f(this->playerCenter.x, this->playerCenter.y + 10.f),
					Vector2f(0.5f, 0.5f),
					Vector2f(1.f, 0.f),
					2.f,
					70.f,
					2.f,
					this->getDamage()
				));
			}
			else if (this->mainGunLevel == 2) {
				this->bullets.add(Bullet(
					&Player::playerBulletTextures[LASER],
					Vector2f(this->playerCenter.x, this->playerCenter.y - 5.f),
					Vector2f(0.5f, 0.5f),
					Vector2f(1.f, 0.f),
					2.f,
					70.f,
					2.f,
					this->getDamage()
				));
				this->bullets.add(Bullet(
					&Player::playerBulletTextures[LASER],
					Vector2f(this->playerCenter.x, this->playerCenter.y),
					Vector2f(0.5f, 0.5f),
					Vector2f(1.f, 0.f),
					2.f,
					70.f,
					2.f,
					this->getDamage()
				));
				this->bullets.add(Bullet(
					&Player::playerBulletTextures[LASER],
					Vector2f(this->playerCenter.x, this->playerCenter.y + 5.f),
					Vector2f(0.5f, 0.5f),
					Vector2f(1.f, 0.f),
					2.f,
					70.f,
					2.f,
					this->getDamage()
				));
			}
			// Animate gun
			this->mainGunSprite.move(-30.f, 0.f);
		}
		else if (this->currentWeapon == MISSILE01) {
			// Create bullet
			this->bullets.add(Bullet(
				&Player::playerBulletTextures[MISSILE01],
				Vector2f(this->playerCenter.x, this->playerCenter.y - 10.f),
				Vector2f(0.5f, 0.2f), 
				Vector2f(1.f, 0.f), 
				2.f, 
				45.f, 
				1.f,
				this->getDamage()
			));
			
			if (this->dualMissiles01) {
				this->bullets.add(Bullet(
					&Player::playerBulletTextures[MISSILE01],
					Vector2f(this->playerCenter.x, this->playerCenter.y + 10.f),
					Vector2f(0.05f, 0.02f), 
					Vector2f(1.f, 0.f), 
					2.f, 
					45.f, 
					1.f,
					this->getDamage()
				));
			}
		}
		else if (this->currentWeapon == MISSILE02) {
			if (this->dualMissiles02) {

			}
		}
		this->shootTimer = 0;  // Reset timer
	}

	// Shielding
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHIELD])) && this->shield) {
		if (this->shieldTimer > 0 && this->shieldRechargeTimer >= this->shieldRechargeTimerMax) {
			this->shielding = true;
			this->shieldTimer -= 2.f * dt * this->dtMultiplier;

			// Deplete shield
			if (this->shieldTimer <= 0.f)
				this->shieldRechargeTimer = 0.f;
		}
		else
			this->shielding = false;
	}
	else
		this->shielding = false;

	// Damaged
	if (this->isDamageCooldown()) {
		if ((int)this->damageTimer % 5 == 0) {
			this->lWing.setColor(Color::Red);
			this->rWing.setColor(Color::Red);
			this->cPit.setColor(Color::Red);
		}
		else {
			this->lWing.setColor(Color::White);
			this->rWing.setColor(Color::White);
			this->cPit.setColor(Color::White);
		}
	}
	else {
		this->lWing.setColor(Color::White);
		this->rWing.setColor(Color::White);
		this->cPit.setColor(Color::White);
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

void Player::setGunLevel(int gunLevel) { 
	this->mainGunLevel = gunLevel; 
	this->mainGunSprite.setTexture(Player::playerMainGunTextures[this->mainGunLevel]);
}

void Player::addStatPointRandom() {
	int r = rand() % 4;
	switch (r) {
	case 0:
		this->power++;
		break;
	case 1:
		this->wiring++;
		break;
	case 2:
		this->cooling++;
		break;
	case 3:
		this->plating++;
		break;
	default:
		break;
	}
	this->updateStats();
}

bool Player::gainExp(int exp) {
	this->exp += exp;
	return this->updateLeveling();
}

void Player::gainHP(int hp) {
	this->hp += hp;
	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::upgradeHP() {
	this->hpAdded += 10;
	this->updateStats();
	this->hp = this->hpMax;
}

bool Player::playerShowStatsIsPressed() {
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::STATS])))
		return true;
	return false;
}

std::string Player::getStatsAsString()const {
	return
		"Level: " + std::to_string(this->level) +
		"\nExp: " + std::to_string(this->exp) + " / " + std::to_string(this->expNext) +
		"\nStatpoints: " + std::to_string(this->statPoints) +
		"\nHP: " + std::to_string(this->hp) + " / " + std::to_string(this->hpMax) + " ( +" + std::to_string(this->hpAdded) + ") "
		"\nDamage: " + std::to_string(this->damage) + " - " + std::to_string(this->damageMax) +
		"\n\nScore: " + std::to_string(this->score) +
		"\n\nPower: " + std::to_string(this->power) +
		"\nPlating: " + std::to_string(this->plating) +
		"\nWiring: " + std::to_string(this->wiring) +
		"\nCooling: " + std::to_string(this->cooling) +
		"\n\nShield Capacity: " + std::to_string(this->shieldTimerMax);
}

void Player::reset() {
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->sprite.setPosition(Vector2f(100.f, 100.f));
	this->bullets.clear();
	this->upgradesAcquired.clear();
	this->setGunLevel(0);
	this->wiring = 0;
	this->cooling = 0;
	this->power = 0;
	this->plating = 0;
	this->dualMissiles01 = false;
	this->dualMissiles02 = false;
	this->shield = false;
	this->piercingShot = false;
	this->currentVelocity.x = 0.f;
	this->currentVelocity.y = 0.f;
	this->level = 1;
	this->exp = 0;
	this->expNext = 20;
	this->currentWeapon = LASER;
	this->statPoints = 0;
	this->shootTimer = this->shootTimerMax;
	this->damageTimer = this->damageTimerMax;
	this->score = 0;
}

void Player::update(View& view, const float& dt) {
	// Update timers
	if (this->powerupRF) {
		this->shootTimerMax = 10.f;
		if (this->shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * this->dtMultiplier;
	}
	else {
		this->shootTimerMax = 20.f;
		if (this->shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * this->dtMultiplier;
	}

	if (this->damageTimer < this->damageTimerMax) 
		this->damageTimer += 1.f * dt * this->dtMultiplier;

	if (this->shieldRechargeTimer < this->shieldRechargeTimerMax)
		this->shieldRechargeTimer += 1.f * dt * this->dtMultiplier;

	if (this->shieldTimer < this->shieldTimerMax && this->shieldRechargeTimer >= this->shieldRechargeTimerMax)
		this->shieldTimer += 1.f * dt * this->dtMultiplier;

	if (this->powerupTimer > 0.f)
		this->powerupTimer -= 1.f * dt * this->dtMultiplier;

	this->movement(view, dt);
	this->changeAccessories(dt);
	this->updateAccessories(dt);
	this->updatePowerups();
	this->combat(dt);
}

void Player::draw(RenderTarget& target) {
	target.draw(this->aura);

	for (size_t i = 0; i < this->bullets.size(); i++) {
		this->bullets[i].draw(target);
	}

	target.draw(this->sprite);
	target.draw(this->lWing);
	target.draw(this->rWing);
	target.draw(this->cPit);
	target.draw(this->mainGunSprite);

	if (this->shielding)
		target.draw(this->deflectorShield);
}




