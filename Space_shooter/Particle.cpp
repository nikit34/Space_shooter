#include "Particle.h"


dArr<Texture> Particle::particleTextures;

Particle::Particle(
	Vector2f pos,
	int textureIndex,
	Vector2f dir,
	float maxVel,
	float maxRotation,
	float lifeTime
) {
	this->dtMultiplier = 60.f;
	this->sprite.setTexture(Particle::particleTextures[textureIndex]);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.setPosition(pos);

	this->dir = dir;

	this->maxVel = maxVel;
	this->maxRotation = maxRotation;

	this->lifeTime = lifeTime;
}

Particle::~Particle() {}

void Particle::update(const float& dt) {
	// Lifetime
	if (this->lifeTime > 0) {
		this->lifeTime -= 1.f * dt * this->dtMultiplier;

		// Reduce alpha
		if (this->sprite.getColor().a > 0) {
			this->sprite.setColor(Color(255, 255, 255, this->sprite.getColor().a - 1 * dt * this->dtMultiplier));

			if (this->sprite.getColor().a > 255)
				this->sprite.setColor(Color(255, 255, 255, 0));
		}

		// Movement
		this->sprite.move(
			this->maxVel * this->dir.x * dt * this->dtMultiplier,
			this->maxVel * this->dir.y * dt * this->dtMultiplier
		);

		this->sprite.setRotation(this->maxRotation * dt * this->dtMultiplier);
	}
}

void Particle::draw(RenderTarget& target) {
	target.draw(this->sprite);
}