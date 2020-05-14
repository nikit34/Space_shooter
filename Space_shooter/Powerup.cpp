#include "Powerup.h"


int Powerup::nrOfPowerups = 2;
dArr<Texture> Powerup::powerupTextures;

Powerup::Powerup(
	int type, 
	float timerMax, 
	Vector2f pos
) {
	this->dtMultiplier = 60.f;
	this->type = type;
	this->timerMax = timerMax;
	this->timer = this->timerMax;

	this->sprite.setTexture(Powerup::powerupTextures[this->type]);
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2);
	this->sprite.setScale(0.5f, 0.5f); 
	this->sprite.setPosition(pos);
}

Powerup::~Powerup() {}

void Powerup::update(const float& dt) {
	// Update timer
	if (this->timer > 0)
		this->timer -= 1.f * dt * this->dtMultiplier;

	this->sprite.rotate(10.f * dt * this->dtMultiplier);
}

void Powerup::draw(RenderTarget& target) {
	target.draw(this->sprite);
}