#include "Boss.h"

enum textures { BODY = 0 };

// Texture role: 0 for body

Boss::Boss(dArr<Texture>& textures,
	Vector2f position,
	int type
) {
	this->textures = &textures;
	this->type;

	switch (this->type) {
	case 0: // First easy boss
		if ((*this->textures).size() > 0) {
			this->sprite.setTexture((*this->textures)[BODY]);
		}
		this->sprite.setPosition(position);
		break;
	case 1:
		break;
	default:
		break;
	}
}

Boss::~Boss() {

}
