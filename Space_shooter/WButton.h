#pragma once
#include"Enemy.h"


class WButton {
public:
	WButton(
		int id,
		Font &font,
		std::string text,
		const unsigned int charSize,
		Vector2f pos,
		Vector2f scale,
		int textureIndex);
	virtual ~WButton();

	// Accessors
	inline std::string getName() { return this->text.getString(); }
	inline int getId() { return this->id; }
	inline FloatRect getBounds() const { return this->sprite.getGlobalBounds(); }

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
	int id;

	Sprite sprite;
	Text text;
	
	bool pressed;
	bool hover;
	bool idle;

	Color colorPressed;
	Color colorHover;
	Color colorIdle;
};

