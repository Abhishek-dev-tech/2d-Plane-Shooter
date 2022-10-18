#include "Game.h"
#include "RenderWindow.h"

Game::Game()
	:window("GAME v1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 720)
{

}

void Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		isRunning = true;
	else
		isRunning = false;

	texture.LoadTextures(window);

	objectSpawner.GetTextures(texture.smallEnemyShip, 
		texture.playerProjectile01, 
		texture.mediumEnemyShip);
}

void Game::Update()
{
	texture.Update();
	objectSpawner.Update();
}

void Game::HandleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

	texture.m_PlayerShip.HandleEvent(event);
}

void Game::Render()
{
	window.clear();
	texture.m_PlayerShip.Render(window);
	texture.Render(window);
	objectSpawner.Render(window);
	window.display();
}


void Game::Clean()
{
	window.cleanUp();
	SDL_Quit();
}