#include"Game.h"


Game::Game(RenderWindow* window) {
	this->window = window;
	this->window->setFramerateLimit(200);
	this->fullscreen = false;
	this->dtMultiplier = 60.f;
	this->scoreMultiplier = 1;
	this->score = 0;
	this->scoreTimer.restart();
	this->scoreTime = 0;
	this->multiplierAdderMax = 10;
	this->multiplierAdder = 0;
	this->multiplierTimerMax = 200.f;
	this->multiplierTimer = this->multiplierTimerMax;
	this->bestScoreSecond = 0.0;
	this->difficulty = 0;
	this->difficultyTimer = 0.f;

	this->stage = nullptr;

	this->paused = true;
	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;

	this->initialize();
}

Game::~Game() {
	delete this->stage;
}


void Game::initView() {
	this->mainView.setSize(Vector2f(this->window->getSize()));
	this->mainView.setCenter(Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2));
}

void Game::initTextures() {
	Texture temp;

	// Map
	Tile::initTextures();

	// Bullet
	Bullet::initTextures();

	// Player
	Player::initTextures();

	// Pickup 
	Pickup::initTextures();

	// Upgrades
	Upgrade::initTextures();

	// Powerup
	Powerup::initTextures();

	// Enemies
	Enemy::initTextures();

	// Bosses


	// Particles
	Particle::initTextures();
}

void Game::initMap() {
	this->stage = new Stage(10, 10);
	this->stage->loadStage("test.wmap", this->mainView);
}

void Game::initUI() {
	Text tempText;

	// Follow text init
	this->followPlayerText.setFont(font);
	this->followPlayerText.setCharacterSize(14);
	this->followPlayerText.setFillColor(Color::White);

	// Static text init
	this->staticPlayerText.setFont(font);
	this->staticPlayerText.setCharacterSize(14);
	this->staticPlayerText.setFillColor(Color::White);
	
	// Bars init
	this->playerExpBar.setSize(Vector2f(40.f, 5.f));
	this->playerExpBar.setFillColor(Color(0.f, 100.f, 200.f, 200.f));

	this->playerShieldBar.setSize(Vector2f(40.f, 5.f));
	this->playerShieldBar.setFillColor(Color(200.f, 0.f, 100.f, 200.f));

	this->playerPowerupBar.setSize(Vector2f(40.f, 5.f));
	this->playerPowerupBar.setFillColor(Color(0.f, 100.f, 100.f, 200.f));

	// Enemy text init
	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(Color::White);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setCharacterSize(40);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2 - 100.f,
		this->window->getSize().y / 2);

	this->scoreText.setFont(this->font);
	this->scoreText.setFillColor(Color(200, 200, 200, 150));
	this->scoreText.setCharacterSize(32);
	this->scoreText.setString("Score: 0");
	this->scoreText.setPosition(10.f, 10.f);

	this->controlsText.setFont(this->font);
	this->controlsText.setCharacterSize(26);
	this->controlsText.setString(
		"A: LEFT\nD: RIGHT\nW: UP\nS: DOWN\nSPACE: SHOOT\nRALT: SHIELD\nTAB: Stats window\nP: PAUSE/CONTROLS (START GAME)\nESC: QUIT\n1,2,3 & 4: CUSTOMIZE SHIP (CAN DO WHILE PAUSED!)\nF11: FULLSCREEN\n\nTOP-LEFT SHIP: Player number\nTOP-RIGHT SHIP: Hp/HpMax\nBOTTOM-LEFT SHIP: Level\nBOTTOM-RIGHT SHIP: Exp-bar\nBOTTOM-RIGHT SHIP: Shield-bar\n\nWARNING, SCORE-TIMER DOES NOT STOP WHEN PAUSED!"
	);
	this->controlsText.setPosition(50.f, 300.f);

	// PlayerStatText init
	this->playerStatsText.setFont(this->font);
	this->playerStatsText.setFillColor(Color::White);
	this->playerStatsText.setCharacterSize(16);
	this->playerStatsText.setString("NONE");

	this->playerStatsTextBack.setFillColor(Color(50, 50, 50, 100));
	this->playerStatsTextBack.setOutlineThickness(1.f);
	this->playerStatsTextBack.setOutlineColor(Color(255, 255, 255, 200));
}

void Game::initialize() {
	// Init view
	this->initView();

	// Init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	// Init textures
	this->initTextures();

	// Init map
	this->initMap();

	// Init players
	this->players.add(Player());

	this->players.add(Player(
		Keyboard::Numpad8,
		Keyboard::Numpad5,
		Keyboard::Numpad4,
		Keyboard::Numpad6,
		Keyboard::RControl,
		Keyboard::RShift,
		Keyboard::Numpad7,
		Keyboard::Numpad1,
		Keyboard::Numpad2,
		Keyboard::Numpad3,
		Keyboard::Numpad0
	));

	//	this->players.add(Player(
		//	Keyboard::I,
		//	Keyboard::K,
		//	Keyboard::J,
		//	Keyboard::L,
		//	Keyboard::RAlt,
		//	Keyboard::Period,
		//	Keyboard::Comma,
		//	Keyboard::Num8,
		//	Keyboard::Num9,
		//	Keyboard::Num0,
		//	Keyboard::Add));

	this->playersAlive = this->players.size();

	// Init enemies

	this->enemySpawnTimerMax = 25.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;

	// Init bosses
	this->bossEncounter = false;

	this->initUI();
}

void Game::updateView() {
	this->mainView.move(this->stage->getScrollSpeed(), 0.f);
}



void Game::update(const float& dt) {
	// Timers update
	this->updateTimers(dt);

	// Fullscreen
	this->toggleFullscreen();

	// Pause game
	this->pauseGame();

	// Update while game paused
	this->updateWhilePaused(dt);

	// Start game
	if (this->playersAlive > 0 && !this->paused) {
		// Update timers
		this->updateTimersUnpaused(dt);

		// View
		this->updateView();

		// Make game harder with time
		this->updateDifficulty();

		// Score timer and multipliers
		this->updateScore();

		//Map update
		this->mapUpdate(dt);

		// Update players, bullets and combat
		this->playerUpdate(dt);

		// Update enemies
		this->enemyUpdate(dt);

		// Update texttags
		this->textTagsUpdate(dt);

		// Upgrades update
		this->upgradesUpdate(dt);

		// Pickups update
		this->pickupsUpdate(dt);

		// Powerups update
		this->powerupsUpdate(dt);

		// Particles update
		this->particlesUpdate(dt);
	}
	else if (this->playersAlive <= 0 && this->scoreTime == 0) {
		// Best score is set
		this->setEndingScoreboard();
	}

	// Restart if all player dead
	if (this->playersAlive <= 0) {
		this->restartUpdate();
	}
}



void Game::updateTimers(const float& dt) {
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;
}

void Game::toggleFullscreen() {
	if (Keyboard::isKeyPressed(Keyboard::F11) && this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;

		if (fullscreen) {
			this->fullscreen = false;
			this->window->close();
			this->window->create(sf::VideoMode(1920, 1080), "SpaceGame", Style::Default);
		}
		else {
			this->fullscreen = true;
			this->window->close();
			this->window->create(sf::VideoMode(1920, 1080), "SpaceGame", Style::Fullscreen);
		}
	}
}

void Game::pauseGame() {
	if (Keyboard::isKeyPressed(Keyboard::P) && this->keyTime >= this->keyTimeMax) {
		if(this->paused)	
			this->paused = false;
		else
			this->paused = true;

		this->keyTime = 0.f;
	}
}

void Game::updateWhilePaused(const float& dt) {
	// Change accessories when paused
	if (this->paused)
	{
		for (size_t i = 0; i < this->players.size(); i++)
		{
			if (this->players[i].isAlive())
			{
				this->players[i].changeAccessories(dt);
			}
		}
	}
}

void Game::updateTimersUnpaused(const float& dt) {
	// Enemy spawn timer
	if (this->enemySpawnTimer < this->enemySpawnTimerMax)
		this->enemySpawnTimer += 1.f * dt * this->dtMultiplier;

	// Difficulty timer
	this->difficultyTimer += 1.f * dt * this->dtMultiplier;

	if (this->multiplierTimer > 0.f) {
		this->multiplierTimer -= 1.f * dt * this->dtMultiplier;

		if (this->multiplierTimer <= 0.f) {
			this->multiplierTimer = 0.f;
			this->multiplierAdder = 0;
			this->scoreMultiplier = 1;
		}
	}
}

void Game::updateDifficulty() {
	if ((int)this->difficultyTimer % 1000 == 0 && this->enemySpawnTimerMax > 10) {
		if(this->enemySpawnTimer > 10)
			this->enemySpawnTimerMax--;
		
		this->difficulty++;
		this->difficultyTimer = 1.f;
	}
}

void Game::updateScore() {
	if (this->multiplierAdder >= this->multiplierAdderMax) {
		this->multiplierAdder = 0;
		this->scoreMultiplier++;
	}
}

void Game::playerUpdate(const float& dt) {
	for (size_t i = 0; i < this->players.size(); i++) {
		if (this->players[i].isAlive()) {
			/// Update Players
			this->players[i].update(this->mainView, dt);

			// Bullet update
			this->playerBulletUpdate(dt, i);

			// Update score
			this->score = 0;

			for (size_t k = 0; k < this->players.size(); k++) {
				this->score += this->players[k].getScore();
			}

			this->scoreText.setString(
				"Score: " + std::to_string(this->score) +
				"\nMultiplier: " + std::to_string(this->scoreMultiplier) + "x" +
				"\nMultiplier Timer: " + std::to_string((int)this->multiplierTimer) +
				"\nNew Multiplier: " + std::to_string(this->multiplierAdder) +
				" / " + std::to_string(this->multiplierAdderMax) +
				"\nGame time: " + std::to_string((int)this->scoreTimer.getElapsedTime().asSeconds()) +
				"\nDifficulty: " + std::to_string(this->difficulty) +
				"\nBest Score/Second: " + std::to_string((int)round(this->bestScoreSecond))
			);
		}
	}
}

void Game::playerBulletUpdate(const float& dt, const int i) {
	bool enemyRemoved = false;
	bool bulletRemoved = false;

	for (size_t k = 0; k < this->players[i].getBulletsSize() && !bulletRemoved; k++) {
		this->players[i].getBullet(k).update(dt);

		// Enemy collision check
		for (size_t j = 0; j < this->enemies.size() && !enemyRemoved; j++) {
			if (this->players[i].getBullet(k).getGlobalBounds().intersects(
				this->enemies[j].getGlobalBounds())) {

				// Enemy take damage
				int damage = this->players[i].getBullet(k).getDamage();
				if (this->enemies[j].getHp() > 0) {
					this->enemies[j].takeDamage(damage);

					// Add particles on enemy damage
					int nrOfPart = rand() % 3 + 1;
					for (size_t l = 0; l < nrOfPart; l++) {
						this->particles.add(Particle(
							this->players[i].getBullet(k).getPosition(),
							0,
							this->players[i].getBullet(k).getVel(),
							rand() % 20 + 10,
							-(rand() % 100) - 50,
							30.f,
							Color(255, 255, 255, 255)
						));
					}

					// Create text tag
					this->textTags.add(TextTag(
						&this->font,
						"- " + std::to_string(damage),
						Color::Red,
						Vector2f(this->enemies[j].getPosition().x + 20.f,
							this->enemies[j].getPosition().y - 20.f),
						Vector2f(1.f, 0.f),
						28,
						20.f,
						true
					));
				}

				// Enemy dead
				if (this->enemies[j].getHp() <= 0) {

					// Add particles on enemy dead
					int nrOfPart = rand() % 5 + 5;
					for (size_t l = 0; l < nrOfPart; l++) {
						this->particles.add(Particle(
							this->players[i].getBullet(k).getPosition(),
							0,
							this->players[i].getBullet(k).getVel(),
							rand() % 20 + 10,
							-(rand() % 100) - 50,
							30.f,
							Color(255, 255, 255, 255)
						));
					}

					// Gain score & reset multiplier timer
					this->multiplierTimer = this->multiplierTimerMax;
					int score = this->enemies[j].getHpMax() * this->scoreMultiplier;
					this->multiplierAdder++;
					this->players[i].gainScore(score);

					// Gain exp
					int exp = this->enemies[j].getHpMax()
						+ (rand() % this->enemies[j].getHpMax() + 1)
						* this->scoreMultiplier;

					// Gain exp tag
					if (this->players[i].getPowerupXP()) {
						exp *= 2;

						this->textTags.add(TextTag(
							&this->font,
							"+ " + std::to_string(exp) +
							" ( x" + std::to_string(this->scoreMultiplier) +
							" x2 PowerUp!) EXP",
							Color::Cyan,
							Vector2f(this->enemies[j].getPosition()),
							Vector2f(1.f, 0.f),
							24,
							40.f,
							true
						));
					}
					else {
						this->textTags.add(TextTag(
							&this->font,
							"+ " + std::to_string(exp) +
							" ( x" + std::to_string(this->scoreMultiplier) +
							" ) EXP",
							Color::Cyan,
							Vector2f(this->enemies[j].getPosition()),
							Vector2f(1.f, 0.f),
							24,
							40.f,
							true
						));
					}

					// Score text tag
					this->textTags.add(TextTag(
						&this->font,
						"+ " + std::to_string(score) + "  ( x " +
						std::to_string(this->scoreMultiplier) + " )",
						Color::White,
						Vector2f(90.f, 10.f),
						Vector2f(1.f, 0.f),
						30,
						30.f,
						true
					));

					// Level up tag
					if (this->players[i].gainExp(exp)) {
						// Create text tag
						this->textTags.add(TextTag(
							&this->font,
							"Level UP!",
							Color::Cyan,
							Vector2f(this->players[i].getPosition().x - 10.f,
								this->players[i].getPosition().y - 20.f),
							Vector2f(0.f, 1.f),
							30,
							40.f,
							true
						));
					}

					// Add upgrade
					int dropChance = rand() % 3;
					int uType = 0;
					switch (dropChance) {
						case 0:
							// Add pickup
							dropChance = rand() % 100 + 1;
							if (dropChance > 80) {
								this->pickups.add(Pickup(
									this->enemies[j].getPosition(),
									0,
									150.f
								));
							}
							break;
						case 1:
							// Add upgrade
							dropChance = rand() % 100 + 1;
							if (dropChance > 90) {
								uType = rand() % Upgrade::nrOfTextures;
								for (size_t k = 0; k < this->players[i].getAcquiredUpgrades().size(); k++) {
									if (uType == this->players[i].getAcquiredUpgrades()[k]) {
										uType = rand() % 1;
									}
								}
								this->upgrades.add(Upgrade(
									this->enemies[j].getPosition(),
									uType,
									500.f
								));
							}
							break;
						case 2:
							// Add powerup
							dropChance = rand() % 100 + 1;
							if (dropChance > 90) {
								uType = rand() % Powerup::nrOfTextures;
								this->powerups.add(Powerup(
									uType,
									300.f,
									this->enemies[j].getPosition()
								));
							}
							break;
						default:
							break;
					}
					enemyRemoved = true;
				}
				// Piercing shot check / remove bullet
				if (!this->players[i].getPiercingShot()) {
					bulletRemoved = true;
				}
				else {
					this->players[i].getBullet(k).setPosition(
						Vector2f(this->enemies[j].getPosition().x +
							this->enemies[j].getGlobalBounds().width +
							this->players[i].getBullet(k).getGlobalBounds().width / 2 +
							1.f,
							this->players[i].getBullet(k).getPosition().y
						)
					);
				}
			}
			if(enemyRemoved)
				this->enemies.remove(j);
		}
		// Window bounds check
		if (this->players[i].getBullet(k).getPosition().x >
			this->mainView.getCenter().x + this->mainView.getSize().x / 2) {
			bulletRemoved = true;
		}
		if(bulletRemoved)
			this->players[i].removeBullet(k);
	}
}

void Game::enemyUpdate(const float& dt) {
	// Spawn enemies
	if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
		this->enemies.add(Enemy(
			this->mainView,
			Vector2f(0.f, 0.f),
			Vector2f(-1.f, 0.f),
			rand() % 3,
			this->players[(rand() % this->playersAlive)].getLevel(),
			rand() % this->playersAlive)
		);

		this->enemySpawnTimer = 0;  // Reset timer
	}

	// Update enemies
	bool enemyRemoved = false;
	bool playerKilled = false;

	// Update enemies
	for (size_t i = 0; i < this->enemies.size() && !enemyRemoved; i++) {
		this->enemies[i].update(dt, this->players[this->enemies[i].getPlayerFollowNr()].getPosition());

		// Eneny player collision
		for (size_t k = 0; k < this->players.size() && !playerKilled; k++) {
			if (this->players[k].isAlive()) {
				if (this->players[k].getBounds().intersects(
					this->enemies[i].getGlobalBounds()) &&
					!this->players[k].isDamageCooldown()) {

					int damage = this->enemies[i].getDamage();

					// player take collision damage
					this->players[k].takeDamage(damage);

					this->enemies[i].collision();

					// Player take damage tag
					this->textTags.add(TextTag(
						&this->font,
						"- " + std::to_string(damage),
						Color::Red,
						Vector2f(this->players[k].getPosition().x + 20.f,
							this->players[k].getPosition().y - 20.f),
						Vector2f(-1.f, 0.f),
						30,
						20.f,
						true
					));

					// Player death
					if (!this->players[k].isAlive())
						playerKilled = true;
				}
			}
			if (playerKilled)
				this->playersAlive--;
		}

		// Enemies out of bounds
		if (this->enemies[i].getPosition().x < this->mainView.getCenter().x - this->mainView.getSize().x / 2 -
			this->enemies[i].getGlobalBounds().width) {
			enemyRemoved = true;
		}
		if (enemyRemoved)
			this->enemies.remove(i);
    }
	this->enemyBulletUpdate(dt);
}

void Game::enemyBulletUpdate(const float& dt) {
	// Enemy bullet update
	bool bulletRemoved = false;
	bool playerKilled = false;
	for (size_t i = 0; i < Enemy::enemyBullets.size() && !bulletRemoved; i++) {
		Enemy::enemyBullets[i].update(dt);

		// Player collision check
		for (size_t k = 0; k < this->players.size() && !playerKilled; k++) {
			if (Enemy::enemyBullets[i].getGlobalBounds().intersects(this->players[k].getBounds()) && this->players[k].isAlive()) {
				int damage = Enemy::enemyBullets[i].getDamage();

				// player take bullet damage
				if (!this->players[k].isShielding()) {
					this->players[k].takeDamage(damage);

					// Player take damage tag
					this->textTags.add(TextTag(
						&this->font,
						"- " + std::to_string(damage),
						Color::Red,
						Vector2f(this->players[k].getPosition().x + 20.f,
							this->players[k].getPosition().y - 20.f),
						Vector2f(-1.f, 0.f),
						30,
						20.f,
						true
					));

					// Player death
					if (!this->players[k].isAlive())
						playerKilled = true;
				}
				else {
					// Add particles on shielding
					int nrOfPart = rand() % 3 + 1;
					for (size_t l = 0; l < nrOfPart; l++) {
						this->particles.add(Particle(
							Enemy::enemyBullets[i].getPosition(),
							0,
							Enemy::enemyBullets[i].getVel(),
							rand() % 20 + 10,
							-(rand() % 100) - 50,
							30.f,
							Color(0, 50, 255, 255)
						));
					}

					// Player shielded tag
					this->textTags.add(TextTag(
						&this->font,
						"- " + std::to_string(0),
						Color::Cyan,
						Vector2f(this->players[k].getPosition().x + 20.f,
							this->players[k].getPosition().y - 20.f),
						Vector2f(-1.f, 0.f),
						30,
						20.f,
						true
					));
				}
				bulletRemoved = true;
			}
			if (playerKilled)
				this->playersAlive--;
		}

		// Window bounds check
		if (!bulletRemoved &&
			(Enemy::enemyBullets[i].getPosition().x > this->mainView.getCenter().x + this->mainView.getSize().x / 2 ||
				Enemy::enemyBullets[i].getPosition().x < this->mainView.getCenter().x - this->mainView.getSize().x / 2 ||
				Enemy::enemyBullets[i].getPosition().y > this->mainView.getCenter().y + this->mainView.getSize().y / 2 ||
				Enemy::enemyBullets[i].getPosition().y < this->mainView.getCenter().y - this->mainView.getSize().y / 2
				)) {
			bulletRemoved = true;
		}
		if (bulletRemoved)
			Enemy::enemyBullets.remove(i);
	}
}

void Game::textTagsUpdate(const float& dt) {
	bool textTagRemoved = false;
	for (size_t i = 0; i < this->textTags.size() && !textTagRemoved; i++) {
		this->textTags[i].update(dt);

		if (this->textTags[i].getTimer() <= 0.f) {
			textTagRemoved = true;
		}
		if (textTagRemoved)
			this->textTags.remove(i);
	}
}

void Game::upgradesUpdate(const float& dt) {
	bool upgradeRemoved = false;
	bool hasUpgrade = false;
	for (size_t i = 0; i < this->upgrades.size() && !upgradeRemoved; i++) {
		this->upgrades[i].update(dt);

		for (size_t k = 0; k < this->players.size(); k++) {
			if (this->upgrades[i].checkCollision(this->players[k].getBounds())) {
				if (this->upgrades[i].getType() != 0 && this->upgrades[i].getType() != 1) {
					for (size_t j = 0; j < this->players[k].getAcquiredUpgrades().size() && !hasUpgrade; j++) {
						if (this->upgrades[i].getType() == this->players[k].getAcquiredUpgrades()[j])
							hasUpgrade = true;
					}
					if (!hasUpgrade)
						this->players[k].getAcquiredUpgrades().add(this->upgrades[i].getType());
				}
					
				switch (this->upgrades[i].getType()) {

				case Upgrade::STAT_POINT: // Statpoint
					this->players[k].addStatPointRandom();

					// HT text tag
					this->textTags.add(
						TextTag(&this->font,
							"RANDOM STATPOINT UPGRADE",
							Color::Yellow,
							Vector2f(this->players[k].getPosition()),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);
					break;

				case Upgrade::HEALTH_TANK: // Healthtank
					this->players[k].upgradeHP();

					// HT text tag
					this->textTags.add(
						TextTag(&this->font,
							"PERMANENT HEALTH UPGRADE",
							Color::Yellow,
							Vector2f(this->players[k].getPosition()),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);
					break;

				case Upgrade::DOUBLE_RAY: // Doubleray
					if (this->players[k].getGunLevel() < 1)
						this->players[k].setGunLevel(1);

					// DR text tag
					this->textTags.add(
						TextTag(&this->font,
							"DOUBLE RAY UPGRADE",
							Color::Yellow,
							Vector2f(this->players[k].getPosition()),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);
					break;

				case Upgrade::TRIPLE_RAY: // Tripleray
					if (this->players[k].getGunLevel() < 2)
						this->players[k].setGunLevel(2);

					// TR text tag
					this->textTags.add(
						TextTag(&this->font,
							"TRIPLE RAY UPGRADE",
							Color::Yellow,
							Vector2f(this->players[k].getPosition()),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);
					break;

				case Upgrade::PIERCING_SHOT: // Piercing
					this->players[k].enablePiercingShot();

					// PS text tag
					this->textTags.add(
						TextTag(&this->font,
							"PIERCING SHOT UPGRADE",
							Color::Yellow,
							Vector2f(this->players[k].getPosition()),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);
					break;

				case Upgrade::SHIELD: // Shield
					this->players[k].enableShield();

					// SH text tag
					this->textTags.add(
						TextTag(&this->font,
							"SHIELD UPGRADE",
							Color::Yellow,
							Vector2f(this->players[k].getPosition()),
							Vector2f(1.f, 0.f),
							40,
							100.f,
							true
						)
					);
					break;

				default:
					break;
				}
				upgradeRemoved = true;
			}
		}
		if (this->upgrades[i].canDelete()) {
			upgradeRemoved = true;
		}
		if (upgradeRemoved)
			this->upgrades.remove(i);
	}
}

void Game::powerupsUpdate(const float& dt) {
	bool powerupRemoved = false;
	for (size_t i = 0; i < this->powerups.size(); i++) {
		this->powerups[i].update(dt);

		for (size_t k = 0; k < this->players.size(); k++) {
			if (this->powerups[i].collide(this->players[k].getBounds())) {
				switch (this->powerups[i].getType()) {
				case Powerup::RAPIDFIRE: // RF
					this->players[k].enablePowerupRF();
					break;
				case Powerup::EXPERIENCE_DOUBLE: // XP
					this->players[k].enablePowerupXP();
					break;
				default:
					break;
				}
				powerupRemoved = true;
			}
		}

		if (this->powerups[i].canRemove()) {
			powerupRemoved = true;
		}
		if (powerupRemoved)
			this->powerups.remove(i);
	}
}

void Game::mapUpdate(const float& dt) {
	this->stage->update(dt, this->mainView, false);
}

void Game::particlesUpdate(const float& dt) {
	bool particleRemoved = false;
	for (size_t i = 0; i < this->particles.size() && !particleRemoved; i++) {
		this->particles[i].update(dt);
	
		if (this->particles[i].readyToDel())
			particleRemoved = true;

		if(particleRemoved)
			this->particles.remove(i);
	}
}

void Game::pickupsUpdate(const float& dt) {
	bool pickupRemoved = false;
	for (size_t i = 0; i < this->pickups.size() && !pickupRemoved; i++) {
		this->pickups[i].update(dt);
		for (size_t k = 0; k < this->players.size(); k++) {
			if (this->pickups[i].checkCollision(this->players[k].getBounds())) {
				int gainHp = this->players[k].getHpMax() / 5;

				switch (this->pickups[i].getType()) {

				case 0: // HP
					if (this->players[k].getHp() < this->players[k].getHpMax()) {
						this->players[k].gainHP(gainHp);

						// Gain HP tag
						this->textTags.add(
							TextTag(&this->font,
								"+ " +
								std::to_string(gainHp) +
								" HP",
								Color::Green,
								Vector2f(this->players[k].getPosition()),
								Vector2f(0.f, -1.f),
								24,
								40.f,
								true
							)
						);
					}
					else {
						// Gain exp tag
						this->textTags.add(
							TextTag(&this->font,
								"+ " +
								std::to_string(10) +
								" EXP",
								Color::Cyan,
								this->pickups[i].getPosition(),
								Vector2f(1.f, 0.f),
								24,
								40.f,
								true
							)
						);
						if (this->players[k].gainExp(10)) {
							this->textTags.add(
								TextTag(&this->font,
									"LEVEL UP!",
									Color::Cyan,
									Vector2f(this->players[k].getPosition().x + 20.f,
										this->players[k].getPosition().y - 20.f),
									Vector2f(0.f, 1.f),
									32,
									40.f,
									true
								)
							);
						}
					}
					break;
				case 1: // MISSILE
					break;
				case 2: // HMISSILE
					break;
				default:
					break;
				}
				pickupRemoved = true;
			}
		}
		if (this->pickups[i].canDelete()) {
			pickupRemoved = true;
		}
		if (pickupRemoved)
			this->pickups.remove(i);
	}
}

void Game::setEndingScoreboard() {
	this->scoreTime = (int)this->scoreTimer.getElapsedTime().asSeconds();

	if (this->scoreTime == 0)
		this->scoreTime = 1;

	this->gameOverText.setString(std::string(
		"GAME OVER:\nScore: " +
		std::to_string(this->score) + "\n" +
		"Time: " + std::to_string(this->scoreTime) + "\n" +
		"Score/Second: " + std::to_string((int)round((double)this->score / (double)this->scoreTime)) + "\n" +
		"F1 to RESTART"
	));

	if ((double)this->score / (double)this->scoreTime > this->bestScoreSecond)
		this->bestScoreSecond = (double)this->score / (double)this->scoreTime;
}

void Game::restartUpdate() {
	if (Keyboard::isKeyPressed(Keyboard::F1)) {
		for (size_t i = 0; i < this->players.size(); i++) {
			this->players[i].reset();
		}
		this->playersAlive = this->players.size();
		this->score = 0;
		this->scoreMultiplier = 1;
		this->multiplierAdder = 0;
		this->scoreTime = 0;
		this->difficulty = 0;
		this->bossEncounter = false;
		this->enemySpawnTimerMax = 35.f;
		this->scoreTimer.restart();
		this->enemies.clear();
		this->upgrades.clear();
		this->pickups.clear();
		this->bosses.clear();
	}
}





void Game::draw() {
	// Clear
	this->window->clear();

	// Set view;
	this->window->setView(this->mainView);

	// Draw map
	this->drawMap();

	// Draw players
	this->drawPlayer();

	// Draw enemies
	this->drawEnemies();

	// Draw pickups
	this->drawPickups();

	// Draw upgrades
	this->drawUpgrades();

	// Draw powerups
	this->drawPowerups();

	// Draw particles
	this->drawParticles();

	// Draw 
	this->drawTextTags();

	// Set view;
	this->window->setView(this->window->getDefaultView());

	// Draw UI
	this->drawUI();

	// Finish draw
	this->window->display();
}

void Game::drawMap() {
	stage->draw(*this->window, this->mainView, false);
}

void Game::drawPlayer() {
	for (size_t i = 0; i < this->players.size(); i++) {
		if (this->players[i].isAlive()) {
			this->players[i].draw(*this->window);

			// UI
			this->updateUIPlayer(i);
			this->window->draw(this->followPlayerText);
			this->window->draw(this->playerExpBar);
			this->window->draw(this->playerShieldBar);
			this->window->draw(this->playerPowerupBar);

			if (this->players[i].playerShowStatsIsPressed()) {
				this->window->draw(this->playerStatsTextBack);
				this->window->draw(this->playerStatsText);
			}
		}
	}
}

void Game::drawEnemies() {
	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].draw(*this->window);

		// UI
		this->updateUIEnemy(i);
		this->window->draw(this->enemyText);
	}

	// Enemy bullets
	for (size_t i = 0; i < Enemy::enemyBullets.size(); i++) {
		Enemy::enemyBullets[i].draw(*this->window);
	}
}

void Game::drawPickups() {
	for (size_t i = 0; i < this->pickups.size(); i++) {
		this->pickups[i].draw(*this->window);
	}
}

void Game::drawUpgrades() {
	for (size_t i = 0; i < this->upgrades.size(); i++) {
		this->upgrades[i].draw(*this->window);
	}
}

void Game::drawPowerups() {
	for (size_t i = 0; i < this->powerups.size(); i++) {
		this->powerups[i].draw(*this->window);
	}
}

void Game::drawParticles() {
	for (size_t i = 0; i < this->particles.size(); i++) {
		this->particles[i].draw(*this->window);
	}
}

void Game::drawUI() {
	// Game over text
	if (this->playersAlive <= 0)
		this->window->draw(this->gameOverText);

	// Score text
	this->window->draw(this->scoreText);

	// Controls text
	if (this->paused)
		this->window->draw(this->controlsText);
}

void Game::drawTextTags() {
	// Draw Texttags
	for (size_t i = 0; i < this->textTags.size(); i++) {
		this->textTags[i].draw(*this->window);
	}
}



void Game::updateUIPlayer(int index) {
	if (index >= 0 && index < this->players.size()) {
		// Follow text
		this->followPlayerText.setPosition(
			this->players[index].getPosition().x - 75.f,
			this->players[index].getPosition().y - 5.f);
		this->followPlayerText.setString(
			std::to_string(this->players[index].getPlayerNr())
			+ "           " +
			this->players[index].getHpAsString()
			+ "\n\n\n\n"
			+ std::to_string(this->players[index].getLevel()));

		// Bars
		this->playerExpBar.setPosition(
			this->players[index].getPosition().x - 50.f,
			this->players[index].getPosition().y + 70.f);
		this->playerExpBar.setScale(
			(static_cast<float>(this->players[index].getExp()) / this->players[index].getExpNext()),
			1.f);

		this->playerShieldBar.setPosition(
			this->players[index].getPosition().x - 50.f,
			this->players[index].getPosition().y + 80.f);
		if (this->players[index].getShieldRechargeTimer() < this->players[index].getShieldRechargeTimerMax()) {
			this->playerShieldBar.setScale((static_cast<float>
				(this->players[index].getShieldRechargeTimer()) / this->players[index].getShieldRechargeTimerMax()),
				1.f);
			if (static_cast<int>(this->players[index].getShieldRechargeTimer()) % 5 == 0)
				this->playerShieldBar.setFillColor(Color::Red);
			else
				this->playerShieldBar.setFillColor(Color(200.f, 200.f, 200.f, 200.f));
		}
		else {
			this->playerShieldBar.setScale((static_cast<float>
				(this->players[index].getShieldTimer()) / this->players[index].getShieldTimerMax()),
				1.f);
			this->playerShieldBar.setFillColor(Color(200.f, 0.f, 100.f, 200.f));
		}

		this->playerPowerupBar.setPosition(
			this->players[index].getPosition().x - 50.f,
			this->players[index].getPosition().y + 90.f);
		this->playerPowerupBar.setScale((static_cast<float>
			(this->players[index].getPowerupTimer()) / this->players[index].getPowerupTimerMax()),
			1.f);

		// Statics box with text
		if (this->players[index].playerShowStatsIsPressed()) {
			this->playerStatsText.setString(this->players[index].getStatsAsString());
			this->playerStatsTextBack.setPosition(
				this->players[index].getPosition().x - 80.f,
				this->players[index].getPosition().y + 110.f
			);
			this->playerStatsTextBack.setSize(Vector2f(
				this->playerStatsText.getGlobalBounds().width,
				this->playerStatsText.getGlobalBounds().height
			));
			this->playerStatsText.setPosition(this->playerStatsTextBack.getPosition());
		}
	}
}

void Game::updateUIEnemy(int index) {
	this->enemyText.setPosition(
		this->enemies[index].getPosition().x,
		this->enemies[index].getPosition().y - this->enemies[index].getGlobalBounds().height
	);

	this->enemyText.setString(
		std::to_string(this->enemies[index].getHp())
		+ "/" +
		std::to_string(this->enemies[index].getHpMax())
	);
}
