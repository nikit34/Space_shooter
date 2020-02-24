#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "dArr.h"

using namespace sf;


class TextTag
{
public:
	TextTag(Font* font, 
		std::string text, 
		const Color color, 
		Vector2f position, 
		unsigned int size,
		float timerMax);
	virtual ~TextTag();

	inline const float& getTimer()const { return this->timer; }
	
	void Update(const float& dt);
	void Draw(RenderTarget &target);

private:
	float dtMultiplier;

	Font *font;
	Text text;

	float speed;
	Vector2f direction;
	float timer;
	float timerMax;
};
