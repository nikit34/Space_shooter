#include"Upgrade.h"


int Upgrade::nrOfUpgrades;
dArr<Texture> Upgrade::upgradeTextures;

Upgrade::Upgrade(
	Vector2f position,
	int type, 
	float aliveTimerMax
) {
	this->dtMultiplier = 60.f;
	
	this->type = type;
	this->aliveTimerMax = aliveTimerMax;
	this->aliveTimer = 0;

	this->sprite.setTexture(Upgrade::upgradeTextures[this->type]);
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);
	this->sprite.setPosition(position);
}

Upgrade::~Upgrade() {

}

bool Upgrade::checkCollision(const FloatRect rect) {
	if (this->sprite.getGlobalBounds().intersects(rect))
		return true;
	return false;
}

void Upgrade::update(const float& dt) {
	if (this->aliveTimer < this->aliveTimerMax)
		this->aliveTimer += 1.f * dt * this->dtMultiplier;
	
	this->sprite.rotate(5.f * dt * this->dtMultiplier);
}

void Upgrade::draw(RenderTarget& target) {
	target.draw(this->sprite);
}