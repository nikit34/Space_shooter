#include "Game.h"

Game::Game(RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(60);

	//Init texture
	playerTexture.loadFromFile("Textures/ship.png");

	//Init player
	player = new Player(&this->playerTexture);
}

Game::~Game()
{
	delete player;
}

void Game::Update()
{
	player->Update();
}

void Game::Draw()
{
	player->Draw();
}