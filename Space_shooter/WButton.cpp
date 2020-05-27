#include "WButton.h"


// Static define
dArr<Texture> WButton::textures;
int WButton::nrOfTextures;
void WButton::initTextures() {
	Texture temp;
	temp.loadFromFile("Textures/Buttons/button01.png");
	WButton::textures.add(temp);
	WButton::nrOfTextures = WButton::textures.size();
}

WButton::WButton(
	int id,
	Font& font,
	std::string text,
	const unsigned int charSize,
	Vector2f pos,
	Vector2f scale,
	int textureIndex
) {
	this->id = id;
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize(charSize);
	this->text.setOutlineThickness(2.f);

	this->colorPressed = Color(50, 100, 50, 200);
	this->colorHover = Color(0, 200, 0, 200);
	this->colorIdle = Color(0, 255, 0, 200);

	this->pressed = false;
	this->hover = false;
	this->idle = true;

	if (textureIndex >= 0 && textureIndex < WButton::nrOfTextures)
		this->sprite.setTexture(WButton::textures[textureIndex]);
	this->sprite.setPosition(pos);
	this->sprite.setColor(this->colorIdle);
	this->sprite.setScale(Vector2f(scale.x, scale.y));

	this->text.setPosition(Vector2f(
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2,
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2));
}

WButton::~WButton() {}


bool WButton::isPressed() {
	return this->pressed;
}

bool WButton::isHover() {
	return this->hover;
}

bool WButton::isIdle() {
	return this->idle;
}

void WButton::update(Vector2f mousePos) {
	if(!Mouse::isButtonPressed(Mouse::Left) && !this->sprite.getGlobalBounds().contains(mousePos)) {
		this->idle = true;
		this->pressed = false;
		this->hover = false;
		this->sprite.setColor(this->colorIdle);
	}
	else if (!Mouse::isButtonPressed(Mouse::Left) && this->sprite.getGlobalBounds().contains(mousePos)) {
		this->hover = true;
		this->pressed = false;
		this->idle = false;
		this->sprite.setColor(this->colorHover);
	}
	else if (Mouse::isButtonPressed(Mouse::Left) && this->sprite.getGlobalBounds().contains(mousePos)) {
		this->pressed = true;
		this->hover = false;
		this->idle = false;
		this->sprite.setColor(this->colorPressed);
	}
}

void WButton::draw(RenderTarget& target) {
	target.draw(this->sprite);
	target.draw(this->text);
}

