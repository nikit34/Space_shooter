#pragma once

#include"SFML\Graphics.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include<iostream>

using namespace sf;


class Player
{
public:
	Player();
	virtual ~Player();

	void Update();

	void Draw();

private:
	Sprite shape;
	RectangleShape hitBox;
	Texture* texture;
};

