#pragma once

#include"TextTag.h"

class Bullet {
public:
	Bullet(Texture* texture, 
		Vector2f position, 
		Vector2f scale,
		Vector2f direction,
		float initialVelocity,
		float maxVelocity,
		float acceleration
	);

	virtual ~Bullet();

	// Accessors
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline void setPosition(Vector2f position) { this->sprite.setPosition(position); }

	// Functions
	void movement(const float& dt);
	void update(const float &dt);
	void draw(RenderTarget& target);

private:
	float dtMultiplier;

	Texture* texture;
	Sprite sprite;

	Vector2f currentVelocity;
	float initialVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
};
