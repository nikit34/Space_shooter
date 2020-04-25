#include "Game.h"

enum textures { player = 0, laser01, missile01, mainGun01};

Game::Game(RenderWindow* window) {
	this->window = window;
	this->window->setFramerateLimit(60);
	this->dtMultiplier = 60.f;
	this->scoreMultiplier = 1;
	this->score = 0;
	this->multiplierAdder = 0;
	this->multiplierAdderMax = 10;
	this->multiplierTimerMax = 100.f;
	this->multiplierTimer = this->multiplierTimerMax;

	// Init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	// Init Textures
	this->InitTextures();

	// Init Players
	this->players.add(Player(
		this->textures,
		this->lWingTextures, 
		this->rWingTextures,
		this->cPitTextures, 
		this->areaTextures,
		this->window->getSize()
	));

	this->players.add(Player(
		this->textures,
		this->lWingTextures,
		this->rWingTextures,
		this->cPitTextures,
		this->areaTextures,
		this->window->getSize(),
		Keyboard::Numpad8,
		Keyboard::Numpad5,
		Keyboard::Numpad4,
		Keyboard::Numpad6,
		Keyboard::Numpad1
	));

	this->playersAlive = this->players.size();

	// Init Enemies

	this->enemySpawnTimerMax = 25.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;

	this->InitUI();
}

Game::~Game() {}

void Game::InitTextures() {
	// Init Textures regular
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/ship.png");
	this->textures.push_back(Texture());
	this->textures[laser01].loadFromFile("Textures/Guns/rayTex01.png");
	this->textures.push_back(Texture());
	this->textures[missile01].loadFromFile("Textures/Guns/missileTex01.png");
	this->textures.push_back(Texture());
	this->textures[mainGun01].loadFromFile("Textures/Guns/gun01.png");

	Texture temp;
	temp.loadFromFile("Textures/enemyMoveLeft.png");
	this->enemyTextures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyFollow.png");
	this->enemyTextures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyMoveLeftShoot.png");
	this->enemyTextures.add(Texture(temp));

	// Init Accessory Textures
	std::ifstream in;

	in.open("Textures/Accessories/leftwings.txt");
	std::string fileName = "";

	if (in.is_open()) {
		while (getline(in, fileName)) {
			Texture temp;
			temp.loadFromFile(fileName);
			this->lWingTextures.add(Texture(temp));
		}
	}

	in.close();

	in.open("Textures/Accessories/rightwings.txt");
	fileName = "";

	if (in.is_open()) {
		while (getline(in, fileName)) {
			Texture temp;
			temp.loadFromFile(fileName);
			this->rWingTextures.add(Texture(temp));
		}
	}

	in.close();

	in.open("Textures/Accessories/cockpits.txt");
	fileName = "";

	if (in.is_open()) {
		while (getline(in, fileName)) {
			Texture temp;
			temp.loadFromFile(fileName);
			this->cPitTextures.add(Texture(temp));
		}
	}

	in.close();

	in.open("Textures/Accessories/auras.txt");
	fileName = "";

	if (in.is_open()) {
		while (getline(in, fileName)) {
			Texture temp;
			temp.loadFromFile(fileName);
			this->areaTextures.add(Texture(temp));
		}
	}

	in.close();
}

void Game::InitUI() {
	Text tempText;
	for (size_t i = 0; i < this->players.size(); i++) {
		// Follow Init Text
		this->followPlayerText.setFont(font);
		this->followPlayerText.setCharacterSize(14);
		this->followPlayerText.setFillColor(Color::White);

		// Static Text Init
		this->staticPlayerText.setFont(font);
		this->staticPlayerText.setCharacterSize(14);
		this->staticPlayerText.setFillColor(Color::White);
	}

	this->playerExpBar.setSize(Vector2f(40.f, 5.f));
	this->playerExpBar.setFillColor(Color(0.f, 100.f, 200.f, 200.f));

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
	this->scoreText.setFillColor(Color(200,200,200,150));
	this->scoreText.setCharacterSize(32);
	this->scoreText.setString("Score: 0");
	this->scoreText.setPosition(10.f, 10.f);
}

void Game::UpdateUIPlayer(int index) {
	if (index >= this->players.size())
		std::cout << "OUT OF BOUNDS! (UPDATEUI)";
	else { // Follow text
		this->followPlayerText.setPosition(
			this->players[index].getPosition().x - 75.f,
			this->players[index].getPosition().y - 5.f);
		this->followPlayerText.setString(
			std::to_string(this->players[index].getPlayerNr())
			+ "           " +
			this->players[index].getHpAsString()
			+ "\n\n\n\n"
			+ std::to_string(this->players[index].getLevel())
		);
	

		// Bars
		this->playerExpBar.setPosition(
			this->players[index].getPosition().x - 50.f,
			this->players[index].getPosition().y + 70.f);
		this->playerExpBar.setScale(
			(static_cast<float>(this->players[index].getExp()) / this->players[index].getExpNext()),
			1.f
		);

		// Static text
	}
}

void Game::UpdateUIEnemy(int index) {
	this->enemyText.setPosition(
		this->enemies[index].getPosition().x, 
		this->enemies[index].getPosition().y - this->enemies[index].getGlobalBounds().height
	);
	this->enemyText.setString(
		std::to_string(this->enemies[index].getHp())
		+ "/" +
		std::to_string(this->enemies[index].getHpMax())
	);
	this->enemies[index].Draw(*this->window);
}

void Game::Update(const float &dt) {
	if (this->playersAlive > 0) {
		// Update timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax) 
			this->enemySpawnTimer += 1.f * dt * this->dtMultiplier;

		// Score timer and multipliers
		if (this->multiplierTimer > 0.f) {
			this->multiplierTimer -= 1.f * dt * this->dtMultiplier;
			
			if (this->multiplierTimer <= 0.f) {
				this->multiplierTimer = 0.f;
				this->multiplierAdder = 0;
				this->scoreMultiplier = 1;
			}
		}

		this->scoreMultiplier = this->multiplierAdder / this->multiplierAdderMax + 1;

		// Spawn enemies
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->enemies.add(Enemy(
				this->enemyTextures, 
				this->window->getSize(), 
				Vector2f(0.f, 0.f),
				Vector2f(-1.f, 0.f), 
				rand() % 3, 
				this->players[(rand() % this->playersAlive)].getLevel(), 
				rand() % this->playersAlive)
			);

			this->enemySpawnTimer = 0;  // Reset timer
		}

		// Update players, bullets and combat
		for (size_t i = 0; i < this->players.size(); i++) {
			if (this->players[i].isAlive()) {
				/// Update Players
				this->players[i].Update(this->window->getSize(), dt);

				// Bullets update
				for (size_t k = 0; k < this->players[i].getBulletsSize(); k++) {
					this->players[i].getBullet(k).Update(dt);

					// Enemy collision check
					for (size_t j = 0; j < this->enemies.size(); j++) {
						if (this->players[i].getBullet(k).getGlobalBounds().intersects(
							this->enemies[j].getGlobalBounds())) {
							this->players[i].removeBullet(k);
							
							// Enemy take damage
							int damage = this->players[i].getDamage();
							if (this->enemies[j].getHp() > 0) {
								this->enemies[j].takeDamage(damage);
								
								// Create text tag
								this->textTags.add(TextTag(
									&this->font,
									"- " + std::to_string(damage),
									Color::Green,
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
								// Gain exp
								int exp = this->enemies[j].getHpMax()
									+ (rand() % this->enemies[j].getHpMax() + 1);
								
								// Gain score & reset multiplier timer
								this->multiplierTimer = this->multiplierTimerMax;
								int score = this->enemies[j].getHpMax() * this->scoreMultiplier;
								this->multiplierAdder++;
								this->players[i].gainScore(score);
								
								// Score text tag
								this->textTags.add(TextTag(
									&this->font,
									"+ " + std::to_string(score) + "  ( x " + std::to_string(this->scoreMultiplier) + " )",
									Color::White,
									Vector2f(90.f, 10.f),
									Vector2f(1.f, 0.f),
									30,
									30.f,
									true
								));

								if (this->players[i].gainExp(exp)){
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
								this->enemies.remove(j);

								// Gain exp tag
								// Create text tag
								this->textTags.add(TextTag(
									&this->font,
									"+ " + std::to_string(damage) + " exp",
									Color::Cyan,
									Vector2f(this->players[i].getPosition().x - 10.f,
										this->players[i].getPosition().y - 20.f),
									Vector2f(0.f, 1.f),
									28,
									30.f,
									true
								));
							}
							return;
						}
					}

					// Window bounds check
					if (this->players[i].getBullet(k).getPosition().x >
						this->window->getSize().x) {
						this->players[i].removeBullet(k);
						return;
					}
				}
			}

			// Update score
			this->score = 0;
			this->score += this->players[i].getScore();
			this->scoreText.setString(
				"Score: " + std::to_string(this->score) +
				"\nMultiplier: " + std::to_string(this->scoreMultiplier) +
				"\nMultiplier Timer: " + std::to_string((int)this->multiplierTimer) +
				"\nNew Multiplier: " + std::to_string(this->multiplierAdder) + 
				" / " + std::to_string(this->multiplierAdderMax)
			);
		}

		// Update Enemies
		for (size_t i = 0; i < this->enemies.size(); i++) {
			this->enemies[i].Update(dt, this->players[this->enemies[i].getPlayerFollowNr()].getPosition());

			// Eneny player collision
			for (size_t k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].isAlive()) {
					if (this->players[k].getGlobalBounds().intersects(
						this->enemies[i].getGlobalBounds()) &&
						!this->players[k].isDamageCooldown()) {
						int damage = this->enemies[i].getDamage();
						this->players[k].takeDamage(damage);
						this->enemies[i].collision();
						
						// Create text tag
						this->textTags.add(TextTag(
							&this->font,
							"-" + std::to_string(damage),
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
							this->playersAlive--;

						return;
					}
				}
			}
			// Enemies out of bounds
			if (this->enemies[i].getPosition().x < 0 -
				this->enemies[i].getGlobalBounds().width) {
				this->enemies.remove(i);
				return;
			}
		}
		// Update Texttags
		for (size_t i = 0; i < this->textTags.size(); i++) {
			this->textTags[i].Update(dt);
			if (this->textTags[i].getTimer() <= 0.f) {
				this->textTags.remove(i);
				break;
			}
		}
	}
}

void Game::DrawUI() {
	// Draw Texttags
	for (size_t i = 0; i < this->textTags.size(); i++) {
		this->textTags[i].Draw(*this->window);
	}

	// Game over text
	if (this->playersAlive <= 0) {
		this->window->draw(this->gameOverText);
	}

	// Score text
	this->window->draw(this->scoreText);
}

void Game::Draw() {
	this->window->clear();

	// Draw players
	for (size_t i = 0; i < this->players.size(); i++) {
		if (this->players[i].isAlive()) {
			this->players[i].Draw(*this->window);
			
			// UI
			this->UpdateUIPlayer(i);
			this->window->draw(this->followPlayerText);
			this->window->draw(this->playerExpBar);
		}
	}

	// Draw enemies
	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].Draw(*this->window);

		// UI
		this->UpdateUIEnemy(i);
		this->window->draw(this->enemyText);
	}

	this->DrawUI();
	this->window->display();
}