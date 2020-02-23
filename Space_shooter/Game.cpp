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
	this->players.push_back(Player(this->textures));
	this->players.push_back(Player(this->textures, Keyboard::Numpad8,
		Keyboard::Numpad2, Keyboard::Numpad4,
		Keyboard::Numpad6, Keyboard::Numpad0));
	this->playersAlive = this->players.size();

	// Init Enemies
	Enemy e1(&this->textures[enemy01], this->window->getSize(),
		Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(1.f, 1.f), 0,
		rand() % 3 + 1, 3, 1);
	this->enemies.push_back(Enemy(e1));

	this->enemySpawnTimerMax = 20;
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
		this->followPlayerText.setString(std::to_string(i));

		// Static Text Init
		this->staticPlayerText.setFont(font);
		this->staticPlayerText.setCharacterSize(14);
		this->staticPlayerText.setFillColor(Color::White);
		this->staticPlayerText.setString("");
	}
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
	}
	// Static text
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
			this->enemies.push_back(Enemy(
				&this->textures[enemy01], this->window->getSize(), Vector2f(0.f, 0.f),
				Vector2f(-1.f, 0.f), Vector2f(1.f, 1.f), 0, rand() % 3 + 1, 3, 1));

			this->enemySpawnTimer = 0;  // Reset timer
		}

		for (size_t i = 0; i < this->players.size(); i++) {

			if (this->players[i].isAlive()) {
				/// Update Players
				this->players[i].Update(this->window->getSize(), dt);

				// Bullets update
				for (size_t k = 0; k < this->players[i].getBullets().size(); k++) {
					this->players[i].getBullets()[k].Update(dt);

					// Enemy collision check
					for (size_t j = 0; j < this->enemies.size(); j++) {
						if (this->players[i].getBullets()[k].getGlobalBounds().intersects(
							this->enemies[j].getGlobalBounds())) {
							this->players[i].getBullets().erase(
								this->players[i].getBullets().begin() + k);
							if (this->enemies[j].getHp() > 0)
								this->enemies[j].takeDamage(this->players[i].getDamage());
							if (this->enemies[j].getHp() <= 0)
								this->enemies.erase(this->enemies.begin() + j);
							return;
						}
					}

					// Window bounds check
					if (this->players[i].getBullets()[k].getPosition().x >
						this->window->getSize().x) {
						this->players[i].getBullets().erase(
							this->players[i].getBullets().begin() + k);
						return;
					}
				}
			}
		}

		// Update Enemies
		for (size_t i = 0; i < this->enemies.size(); i++) {
			this->enemies[i].Update(dt);

			// Eneny player collision
			for (size_t k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].isAlive()) {
					if (this->players[k].getGlobalBounds().intersects(
									this->enemies[i].getGlobalBounds())) {
						this->players[k].takeDamage(this->enemies[i].getDamage());
						if (!this->players[k].isAlive())
							this->playersAlive--;
						this->enemies.erase(this->enemies.begin() + i);
						return;
					}
				}
			}

			// Enemies out of bounds
			if (this->enemies[i].getPosition().x < 0 -
				this->enemies[i].getGlobalBounds().width) {
				this->enemies.erase(this->enemies.begin() + i);
				return;
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
		}
	}

	// Game over text
	if (this->playersAlive <= 0) {
		this->window->draw(this->gameOverText);
	}
	this->window->display();
}