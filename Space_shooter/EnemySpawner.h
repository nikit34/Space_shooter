#pragma once

#include"MainMenu.h"

class EnemySpawner {
public:
	EnemySpawner(Vector2i gridPos,
		bool randomSpawnPos,
		int type,
		int levelInterval,
		int nrOfEnemies
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
	bool randomSpawnPos;
	int type; // -1 random
	int levelInterval;
	int nrOfEnemies; // -1 random
};

