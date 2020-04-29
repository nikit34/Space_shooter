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
	void Movement(const float& dt);
	void Update(const float &dt);
	void Draw(RenderTarget& target);

private:
	float dtMultiplier;

	Texture* texture;
	Sprite sprite;

	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
};
