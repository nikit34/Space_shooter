#include "Boss.h"

enum textures { BODY = 0 };

// Texture role: 0 for body, 1 for regular gun, 2 for regular bullet 

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

			this->guns.add(BossGun(&(*this->textures)[1], Vector2f(0.f, 0.f), 20.f));
			this->guns.add(BossGun(&(*this->textures)[1], Vector2f(0.f, 0.f), 20.f));
			this->guns.add(BossGun(&(*this->textures)[1], Vector2f(0.f, 0.f), 20.f));
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
