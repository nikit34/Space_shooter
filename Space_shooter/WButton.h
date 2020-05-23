#pragma once
#include"Enemy.h"


class WButton {
public:
	WButton(Font &font,
		std::string text,
		const unsigned int charSize,
		Vector2f pos,
		int textureIndex);
	virtual ~WButton();

	bool isPressed();
	bool isHover();
	bool isIdle();

	void update(Vector2f mousePos);
	void draw(RenderTarget& target);
	
	// Static 
	static dArr<Texture> textures;
	static int nrOfTextures;
	static void initTextures();

private:
	Sprite sprite;
	Text text;
	
	bool pressed;
	bool hover;
	bool idle;

	Color colorPressed;
	Color colorHover;
	Color colorIdle;
};

