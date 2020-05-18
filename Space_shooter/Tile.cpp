#include"Tile.h"

Texture Tile::tileTextures;

Tile::Tile(
	IntRect textureRect,
	Vector2f pos,
	bool isCollider,
	bool isDamaging
) {
	this->sprite.setTexture(Tile::tileTextures);
	this->sprite.setTextureRect(textureRect);
	this->sprite.setPosition(pos);

	this->isCollider = isCollider;
	this->isDamaging = isDamaging;
	this->damage = 0;
}

Tile::~Tile() {}

std::string Tile::getAsString()const {
	return
		// IntRect
		std::to_string(this->sprite.getTextureRect().left) + " " +
		std::to_string(this->sprite.getTextureRect().top) + " " +
		std::to_string(this->sprite.getTextureRect().width) + " " +
		std::to_string(this->sprite.getTextureRect().height) + " " +
		// Position Vector2f
		std::to_string((int)this->sprite.getPosition().x / Wingman::gridSize) + " " +
		std::to_string((int)this->sprite.getPosition().y / Wingman::gridSize) + " " +
		// Stats
		std::to_string(isCollider) + " " +
		std::to_string(isDamaging) + " " +
		std::to_string(damage) + " ";
}

void Tile::update(const float &dt) {

}

void Tile::draw(RenderTarget& target) {
	target.draw(this->sprite);
}