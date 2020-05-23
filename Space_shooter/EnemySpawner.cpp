#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(
	Vector2i gridPos,
	bool randomSpawnPos,
	int maxVelocity,
	int type,
	int levelInterval,
	int nrOfEnemies
) {
	this->used = false;
	this->gridPosition = gridPos;
	this->randomSpawnPos = randomSpawnPos;
	this->maxVelocity = maxVelocity;
	this->type = type;
	this->levelInterval = levelInterval;
	this->nrOfEnemies = nrOfEnemies;
}

EnemySpawner::~EnemySpawner() {

}

void EnemySpawner::updateTimer() {

}

bool EnemySpawner::isInScreen(View& view) {
	return 0;
}

void EnemySpawner::spawn() {

}

std::string EnemySpawner::getAsString()const {
	return
		std::to_string(this->gridPosition.x) + " " +
		std::to_string(this->gridPosition.y) + " " +
		std::to_string(this->randomSpawnPos) + " " +
		std::to_string(this->maxVelocity) + " " +
		std::to_string(this->type) + " " +
		std::to_string(this->levelInterval) + " " +
		std::to_string(this->nrOfEnemies) + " ";
}

void EnemySpawner::update(View& view) {

}

void EnemySpawner::draw(RenderTarget& target, Font& font) {
	RectangleShape shape;
	shape.setFillColor(Color::White);
	shape.setSize(Vector2f(Wingman::gridSize, Wingman::gridSize));
	shape.setPosition(this->gridPosition.x * Wingman::gridSize, this->gridPosition.y * Wingman::gridSize);
	if (this->type >= 0)
		shape.setTexture(&Enemy::textures[this->type]);

	Text text;
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(Color::Red);
	text.setPosition(shape.getPosition());
	text.setString(
		"Type    : " + std::to_string(this->type) + "\n" +
		"Level   : " + std::to_string(this->levelInterval) + "\n" +
		"Number  : " + std::to_string(this->nrOfEnemies) + "\n" +
		"Velocity: " + std::to_string(this->maxVelocity) + "\n"
	);

	target.draw(shape);
	target.draw(text);
}
