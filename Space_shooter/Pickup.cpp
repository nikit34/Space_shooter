#include"Pickup.h"

Pickup::Pickup(
	dArr<Texture>& textures,
	Vector2f position,
	int type,
	float duration
) {
	this->dtMultiplier = 60.f;

	this->textures = &textures;
	this->type = type;

	this->sprite.setTexture((*this->textures)[this->type]);

	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);
	this->sprite.setPosition(position);
	this->sprite.setColor(Color(255, 255, 255, 200));
	this->aliveTimerMax = duration;
	this->aliveTimer = 0;
}

Pickup::~Pickup() {}

bool Pickup::checkCollision(FloatRect rect) {
	if (this->sprite.getGlobalBounds().intersects(rect))
		return true;
	return false;
}

void Pickup::update(const float& dt) {
	if (this->aliveTimer < this->aliveTimerMax) 
		this->aliveTimer += 1.f * dt * this->dtMultiplier;

	this->sprite.rotate(5.f * dt * this->dtMultiplier);
}

void Pickup::draw(RenderTarget& target) {
	target.draw(this->sprite);
}