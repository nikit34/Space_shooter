#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(
	Vector2i gridPos,
	int type,
	int level,
	int levelInterval,
	int nrOfEnemies,
	float spawnTimerMax
) {
	this->gridPosition = gridPos;
	this->type = type;
	this->level = level;
	this->levelInterval = level;
	this->nrOfEnemies = nrOfEnemies;
	this->spawnTimerMax = spawnTimerMax;
	this->spawnTimer = this->spawnTimerMax;
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

void EnemySpawner::update(View& view) {

}

void EnemySpawner::draw(RenderTarget& target) {
	RectangleShape shape;
	shape.setFillColor(Color::White);
	shape.setSize(Vector2f(Wingman::gridSize, Wingman::gridSize));
	shape.setPosition(this->gridPosition.x * Wingman::gridSize, this->gridPosition.y * Wingman::gridSize);
	target.draw(shape);
}
