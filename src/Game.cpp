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

	SDL_ShowCursor(SDL_DISABLE);

	texture.LoadTextures(window);

	objectSpawner.SetTextures(texture.smallEnemyShips,
		texture.projectile01, 
		texture.mediumEnemyShips, 
		texture.bigEnemyShips,
		texture.missile,
		texture.hitMark);

	objectSpawner.SetEntity(&texture.m_PlayerShip);
}

void Game::Update()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	texture.m_Cursor.SetPos(Vector2f(mouseX, mouseY));

	texture.Update();
	objectSpawner.Update();

	CheckCollision();

	srand(SDL_GetTicks());
}

void Game::CheckCollision()
{
	for (int i = 0; i < texture.m_PlayerShip.GetPlayerProjectiles().size(); i++)
	{
		for (int j = 0; j < objectSpawner.GetSmallEnemies().size(); j++)
		{
			if (SDL_HasIntersection(&texture.m_PlayerShip.GetPlayerProjectiles()[i].GetDst(), &objectSpawner.GetSmallEnemies()[j].GetDst()) 
				&& !texture.m_PlayerShip.GetPlayerProjectiles()[i].IsDestroy()
				&& !objectSpawner.GetSmallEnemies()[j].IsDestroy())
			{
				objectSpawner.SpawnHitMarkers(texture.m_PlayerShip.GetPlayerProjectiles()[i].GetPos());
				objectSpawner.GetSmallEnemies()[j].Damage(1);
				texture.m_PlayerShip.GetPlayerProjectiles()[i].Destroy();

				break;

			}
		}

		for (int j = 0; j < objectSpawner.GetMediumEnemies().size(); j++)
		{
			if (SDL_HasIntersection(&texture.m_PlayerShip.GetPlayerProjectiles()[i].GetDst(), &objectSpawner.GetMediumEnemies()[j].GetDst()) 
				&& !texture.m_PlayerShip.GetPlayerProjectiles()[i].IsDestroy()
				&& !objectSpawner.GetMediumEnemies()[j].IsDestroy())
			{
				objectSpawner.SpawnHitMarkers(texture.m_PlayerShip.GetPlayerProjectiles()[i].GetPos());
				objectSpawner.GetMediumEnemies()[j].Damage(1);
				texture.m_PlayerShip.GetPlayerProjectiles()[i].Destroy();
				break;
			}
		}

		for (int j = 0; j < objectSpawner.GetBigEnemies().size(); j++)
		{
			if (SDL_HasIntersection(&texture.m_PlayerShip.GetPlayerProjectiles()[i].GetDst(), &objectSpawner.GetBigEnemies()[j].GetDst()) 
				&& !texture.m_PlayerShip.GetPlayerProjectiles()[i].IsDestroy()
				&& !objectSpawner.GetBigEnemies()[j].IsDestroy())
			{
				objectSpawner.SpawnHitMarkers(texture.m_PlayerShip.GetPlayerProjectiles()[i].GetPos());
				objectSpawner.GetBigEnemies()[j].Damage(1);
				texture.m_PlayerShip.GetPlayerProjectiles()[i].Destroy();
				break;
			}
		}

	}

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
	objectSpawner.Render(window);
	texture.Render(window);
	window.display();
}


void Game::Clean()
{
	window.cleanUp();
	SDL_Quit();
}