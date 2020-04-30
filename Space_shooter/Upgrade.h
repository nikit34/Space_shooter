#pragma once

#include"Boss.h"

class Upgrade {
public:
	Upgrade(
		dArr<Texture>& textures, 
		Vector2f position,
		int type,
		float aliveTimerMax
	);
	virtual ~Upgrade();

	inline const int& getType() { return this->type; }
	inline bool canDelete() { return this->aliveTimer >= this->aliveTimerMax; }

	bool checkCollision(FloatRect rect);

	void Update(const float& dt);
	void Draw(RenderTarget& target);

private:
	float dtMultiplier;

	int type;
	
	float aliveTimer;
	float aliveTimerMax;

	dArr<Texture>* textures;

	Sprite sprite;
};