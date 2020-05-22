#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(
	Vector2i gridPos,
	int type,
	int levelInterval,
	int nrOfEnemies,
	float spawnTimerMax
) {
	this->gridPosition = gridPos;
	this->type = type;
	this->levelInterval = levelInterval;
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

void EnemySpawner::draw(RenderTarget& target, Font& font) {
	RectangleShape shape;
	shape.setFillColor(Color::White);
	shape.setSize(Vector2f(Wingman::gridSize, Wingman::gridSize));
	shape.setPosition(this->gridPosition.x * Wingman::gridSize, this->gridPosition.y * Wingman::gridSize);

	Text text;
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(Color::Red);
	text.setPosition(shape.getPosition());
	text.setString(
		"Type: " + std::to_string(this->type) + "\n" +
		"LevelInterval: " + std::to_string(this->levelInterval) + "\n" +
		"NrOfEnemies: " + std::to_string(this->nrOfEnemies) + "\n" +
		"Timer: " + std::to_string(this->spawnTimer) + "\n"
	);

	target.draw(shape);
	target.draw(text);
}
