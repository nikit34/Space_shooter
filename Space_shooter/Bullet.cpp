#include "Bullet.h"

Bullet::Bullet(Texture* texture, 
	Vector2f position, 
	Vector2f scale,
	Vector2f direction, 
	float initialVelocity, 
	float maxVelocity,
	float acceleration
) {
	this->dtMultiplier = 60.f;
	this->texture = texture;
	this->maxVelocity = maxVelocity;
	this->direction = direction;
	this->acceleration = acceleration;
	this->currentVelocity = Vector2f(
		initialVelocity * this->direction.x,
		initialVelocity * this->direction.y);

	this->sprite.setTexture(*this->texture);
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2);
	this->sprite.setScale(scale);
	this->sprite.setPosition(position);
	this->sprite.setRotation(atan2(this->direction.y, this->direction.x) * 180 / 3.14 + 270);
}

Bullet::~Bullet() {}

void Bullet::Movement(const float &dt) {
	if (this->acceleration > 0.f) {
		if (this->currentVelocity.x < this->maxVelocity)
			this->currentVelocity.x += this->acceleration * this->direction.x
			* dt * this->dtMultiplier;
		if (this->currentVelocity.y < this->maxVelocity)
			this->currentVelocity.y += this->acceleration * this->direction.y
			* dt * this->dtMultiplier;
	}
	else {
		this->currentVelocity = Vector2f(this->maxVelocity * this->direction.x,
			this->maxVelocity * this->direction.y);
	}
	this->sprite.move(this->currentVelocity * dt * this->dtMultiplier);
}

void Bullet::Update(const float &dt) { this->Movement(dt); }

void Bullet::Draw(RenderTarget& target) { target.draw(this->sprite); }