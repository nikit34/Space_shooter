#pragma once

#include"Pickup.h"

class TextTag
{
public:
	TextTag(Font* font, 
		std::string text, 
		const Color color, 
		Vector2f position,
		Vector2f direction,
		unsigned int size,
		float timerMax,
		bool accelerate
	);

	virtual ~TextTag();

	inline const float& getTimer()const { return this->timer; }
	
	void update(const float& dt);
	void draw(RenderTarget &target);

private:
	float dtMultiplier;

	Font *font;
	Text text;

	float speed;
	Vector2f direction;
	float timer;
	float timerMax;
	bool accelerate;
};
