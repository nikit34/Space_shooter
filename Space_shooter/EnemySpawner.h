#pragma once

#include"MainMenu.h"

class EnemySpawner {
public:
	EnemySpawner(Vector2i gridPos,
		int type,
		int levelInterval,
		int nrOfEnemies,
		float spawnTimerMax
	);
	virtual ~EnemySpawner();

	void updateTimer();
	bool isInScreen(View& view);
	void spawn();
	std::string getAsString()const;

	void update(View& view);
	void draw(RenderTarget& target, Font& font);

private:
	Vector2i gridPosition;
	int type; // -1 random
	int levelInterval;
	int nrOfEnemies; // -1 random
	float spawnTimerMax;
	float spawnTimer;
};

