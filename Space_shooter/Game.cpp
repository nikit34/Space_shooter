#include "Game.h"

Game::Game(RenderWindow *window)
{
	this->window = window;
	this->window->setFramerateLimit(60);

	//Init font
	this->font.loadFromFile("Fonts/play_the_game.ttf");

	//Init texture
	this->playerTexture.loadFromFile("Textures/ship.png");
	this->bulletTexture.loadFromFile("Textures/bullet.png");

	//Init player
	this->players.push_back(Player(&playerTexture, &bulletTexture));
	/*
	this->players.push_back(Player(&playerTexture, &bulletTexture, 
		Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::RShift));
	*/

	this->InitUI();
}

Game::~Game()
{
	
}

void Game::InitUI()
{
	Text tempText;
	for (size_t i = 0; i < this->players.size(); i++)
	{
		//Follow Init Text
		tempText.setFont(font);
		tempText.setCharacterSize(12);
		tempText.setFillColor(Color::White);
		tempText.setString(std::to_string(i));
		this->followPlayerTexts.push_back(tempText);

		//Static Text Init
		tempText.setFont(font);
		tempText.setCharacterSize(12);
		tempText.setFillColor(Color::White);
		tempText.setString(" ");
		this->staticPlayerTexts.push_back(tempText);
	}
}

void Game::UpdateUI()
{

}

void Game::Update()
{
	for (size_t i = 0; i < this->players.size(); i++)
	{
		///UIUpdate Players
		this->players[i].Update(this->window->getSize());
		
		//Bullets update
		for (int k = 0; k < this->players[i].getBullets().size(); k++)
		{
			this->players[i].getBullets()[k].Update();

			//Window bounds check
			if (this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x - 100)
			{
				this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
				break;
			}
			//Enemy collision check
		}
		//Update UI
		this->UpdateUI();
	}
}

void Game::DrawUI()
{
	for (size_t i = 0; i < this->followPlayerTexts.size(); i++)
	{
		this->window->draw(this->followPlayerTexts[i]);
	}
	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++)
	{
		this->window->draw(this->staticPlayerTexts[i]);
	}
}

void Game::Draw()
{
	this->window->clear();

	for (size_t i = 0; i < this->players.size(); i++)
	{
		this->players[i].Draw(*this->window);
	}

	this->DrawUI();
	this->window->display();
}