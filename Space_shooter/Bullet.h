﻿#pragma once

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
	inline Vector2f getNormDir() { return normalize(this->currentVelocity, vectorLength(this->currentVelocity)); }
	inline Vector2f getVel()const { return this->currentVelocity; }

	// Functions
	void movement(const float& dt);
	
	void update(const float &dt);
	void draw(RenderTarget& target);

	// Regular functions
	float vectorLength(Vector2f v) {
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}

	Vector2f normalize(Vector2f v, float length) {
		if (length == 0)
			return Vector2f(0.f, 0.f);
		else
			return v / length;
	}

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
