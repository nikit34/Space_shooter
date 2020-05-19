#include "Powerup.h"


dArr<Texture> Powerup::textures;
int Powerup::nrOfTextures;
void Powerup::initTextures() {
	Texture temp;

	temp.loadFromFile("Textures/Powerups/powerupRF.png");
	Powerup::textures.add(Texture(temp));
	temp.loadFromFile("Textures/Powerups/powerupXP.png");
	Powerup::textures.add(Texture(temp));

	Powerup::nrOfTextures = Powerup::textures.size();
}

Powerup::Powerup(
	int type, 
	float timerMax, 
	Vector2f pos
) {
	this->dtMultiplier = 60.f;

	if (type >= Powerup::nrOfTextures) {
		type = Powerup::nrOfTextures - 1;
	}
	else if (type < 0) {
		type = 0;
	}

	this->type = type;
	this->timerMax = timerMax;
	this->timer = this->timerMax;

	this->sprite.setTexture(Powerup::textures[this->type]);
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