#pragma once

#include"SFML\Graphics.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include<iostream>

using namespace sf;


class Player
{
public:
	Player(Texture *texture);
	virtual ~Player();

	void Movement();
	void Update();
	void Draw(RenderTarget &target);

private:
	Sprite sprite;
	RectangleShape hitBox;
	Texture *texture;

	int level;
	int exp;
	int expNext;

	int hp;
	int hpMax;

	int damage;
	int damageMax;

	int score;
};