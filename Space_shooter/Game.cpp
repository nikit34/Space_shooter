#include "Game.h"

enum textures { player = 0, laser01, missile01, mainGun01, enemy01 };

Game::Game(RenderWindow* window) {
	this->window = window;
	this->window->setFramerateLimit(60);
	this->dtMultiplier = 60.f;

	// Init font
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	// Init textures
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/ship.png");
	this->textures.push_back(Texture());
	this->textures[laser01].loadFromFile("Textures/Guns/rayTex01.png");
	this->textures.push_back(Texture());
	this->textures[missile01].loadFromFile("Textures/Guns/missileTex01.png");
	this->textures.push_back(Texture());
	this->textures[mainGun01].loadFromFile("Textures/Guns/gun01.png");
	this->textures.push_back(Texture());
	this->textures[enemy01].loadFromFile("Textures/enemy.png");

	// Init Players
	this->players.add(Player(this->textures));
	this->players.add(Player(this->textures, Keyboard::Numpad8,
		Keyboard::Numpad5, Keyboard::Numpad4,
		Keyboard::Numpad6, Keyboard::Numpad1));
	this->playersAlive = this->players.size();

	// Init Enemies

	this->enemySpawnTimerMax = 25.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;

	this->InitUI();
}

Game::~Game() {}

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
}

void Game::UpdateUIPlayer(int index) {
	if (index >= this->players.size())
		std::cout << "OUT OF BOUNDS! (UPDATEUI)";
	else { // Follow text
		this->followPlayerText.setPosition(
			this->players[index].getPosition().x,
			this->players[index].getPosition().y - 20.f);
		this->followPlayerText.setString(
			std::to_string(this->players[index].getPlayerNr())
			+ "       " +
			this->players[index].getHpAsString()
			+ "\n\n\n\n"
			+ std::to_string(this->players[index].getLevel())
		);
	

		// Bars
		this->playerExpBar.setPosition(
			this->players[index].getPosition().x + 10.f,
			this->players[index].getPosition().y + 60.f);
		this->playerExpBar.setScale(
			(static_cast<float>(this->players[index].getExp()) / this->players[index].getExpNext()),
			1.f
		);

		// Static text
	}
}

void Game::UpdateUIEnemy(int index) {
	this->enemyText.setPosition(this->enemies[index].getPosition());
	this->enemyText.setString(
		std::to_string(this->enemies[index].getHp())
		+ "/" +
		std::to_string(this->enemies[index].getHpMax()));
	this->enemies[index].Draw(*this->window);
}

void Game::Update(const float &dt) {
	if (this->playersAlive > 0) {
		// Update timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax) 
			this->enemySpawnTimer += 1.f * dt * this->dtMultiplier;

		// Spawn enemies
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->enemies.add(Enemy(
				&this->textures[enemy01], this->window->getSize(), Vector2f(0.f, 0.f),
				Vector2f(-1.f, 0.f), Vector2f(1.f, 1.f), rand() % 2, rand() % 3 + 1, 2, 1, rand() % this->playersAlive));

			this->enemySpawnTimer = 0;  // Reset timer
		}

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
								if (this->players[i].gainExp(exp)){
									// Create text tag
									this->textTags.add(TextTag(
										&this->font,
										"Level UP!",
										Color::Cyan,
										Vector2f(this->players[i].getPosition().x + 20.f,
											this->players[i].getPosition().y - 20.f),
										Vector2f(0.f, 1.f),
										30,
										20.f,
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
									Vector2f(this->players[i].getPosition().x + 20.f,
										this->players[i].getPosition().y - 20.f),
									Vector2f(0.f, 1.f),
									28,
									20.f,
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
		}

		// Update Enemies
		for (size_t i = 0; i < this->enemies.size(); i++) {
			this->enemies[i].Update(dt, this->players[this->enemies[i].getPlayerFollowNr()].getPosition());

			// Eneny player collision
			for (size_t k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].isAlive()) {
					if (this->players[k].getGlobalBounds().intersects(
									this->enemies[i].getGlobalBounds())) {
						int damage = this->enemies[i].getDamage();
						this->players[k].takeDamage(damage);
						
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
						this->enemies.remove(i);
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

}

void Game::Draw() {
	this->window->clear();
	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].Draw(*this->window);

		// UI
		this->UpdateUIEnemy(i);
		this->window->draw(this->enemyText);
	}

	for (size_t i = 0; i < this->players.size(); i++) {
		if (this->players[i].isAlive()) {
			this->players[i].Draw(*this->window);
			
			// UI
			this->UpdateUIPlayer(i);
			this->window->draw(this->followPlayerText);
			this->window->draw(this->playerExpBar);
		}
	}

	// Draw Texttags
	for (size_t i = 0; i < this->textTags.size(); i++) {
		this->textTags[i].Draw(*this->window);
	}

	// Game over text
	if (this->playersAlive <= 0) {
		this->window->draw(this->gameOverText);
	}
	this->window->display();
}