#include"Stage.h"

int Stage::gridSize = 50;

Stage::Stage():creationTile(
		IntRect(0, 0, 0, 0), 
		Vector2f(0.f, 0.f), 
		false, 
		false
	){

	for (size_t i = 0; i < 100; i++) {
		this->tiles.add(dArr<std::string>());

		for (size_t k = 0; k < 100; k++) {
			this->tiles[i].add(std::string("0 0 50 50 500 500 0 0"));
		}
	}
}

Stage::~Stage() {}

void Stage::update(
	int fromCol, int toCol,
	int fromRow, int toRow
) {

}

void Stage::draw(RenderTarget& target, 
	int fromCol, int toCol, 
	int fromRow, int toRow
) {
	int rectX = 0;
	int rectY = 0;
	int rectWidth = 0;
	int rectHeight = 0;
	float posX = 0.f;
	float posY = 0.f;
	bool collider = false;
	bool damaging = false; 

	std::stringstream ss;

	for (size_t i = 0; i < this->tiles.size(); i++) {
		for (size_t k = 0; k < this->tiles[0].size(); k++) {
			ss.str(this->tiles[i][k]);

			this->creationTile.setTexRect(rectX, rectY, rectWidth, rectHeight);
			this->creationTile.setPos(posX, posY);
			this->creationTile.setIsCollider(collider);
			this->creationTile.setIsDamaging(damaging);

			this->creationTile.draw(target);
		}
	}
}