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

	Texture::GetInstance().LoadTextures(window);
}

void Game::Update()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	Texture::GetInstance().m_Cursor.SetPos(Vector2f(mouseX, mouseY));

	Texture::GetInstance().Update();
	ObjectSpawner::GetInstance().Update();

	CheckCollision();

	srand(SDL_GetTicks());
}

void Game::CheckCollision()
{

	//Collosion between enemy missile and player
	for (int i = 0; i < ObjectSpawner::GetInstance().GetBigEnemies().size(); i++)
	{
		for (int j = 0; j < ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().size(); j++)
		{
			if (SDL_HasIntersection(&Texture::GetInstance().m_PlayerShip.GetDst(), &ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles()[j].GetDst())
				&& !ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles()[j].IsDestroy())
			{
				ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles()[j].Destroy();
				ObjectSpawner::GetInstance().SpawnBlastEffect(ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles()[j].GetPos(), Vector2f(5, 5));
				ObjectSpawner::GetInstance().SpawnSmokEffect(ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles()[j].GetPos(), Vector2f(5, 5));
			}
		}
	}

	//Collosion between enemy and player bullets
	for (int i = 0; i < Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles().size(); i++)
	{
		for (int j = 0; j < ObjectSpawner::GetInstance().GetSmallEnemies().size(); j++)
		{
			if (SDL_HasIntersection(&Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].GetDst(), &ObjectSpawner::GetInstance().GetSmallEnemies()[j].GetDst())
				&& !Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].IsDestroy()
				&& !ObjectSpawner::GetInstance().GetSmallEnemies()[j].IsDestroy())
			{
				ObjectSpawner::GetInstance().SpawnHitMarkers(Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].GetPos());
				ObjectSpawner::GetInstance().GetSmallEnemies()[j].Damage(1);
				Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].Destroy();

				break;

			}
		}

		for (int j = 0; j < ObjectSpawner::GetInstance().GetMediumEnemies().size(); j++)
		{
			if (SDL_HasIntersection(&Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].GetDst(), &ObjectSpawner::GetInstance().GetMediumEnemies()[j].GetDst())
				&& !Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].IsDestroy()
				&& !ObjectSpawner::GetInstance().GetMediumEnemies()[j].IsDestroy())
			{
				ObjectSpawner::GetInstance().SpawnHitMarkers(Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].GetPos());
				ObjectSpawner::GetInstance().GetMediumEnemies()[j].Damage(1);
				Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].Destroy();
				break;
			}
		}

		for (int j = 0; j < ObjectSpawner::GetInstance().GetBigEnemies().size(); j++)
		{
			if (SDL_HasIntersection(&Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].GetDst(), &ObjectSpawner::GetInstance().GetBigEnemies()[j].GetDst())
				&& !Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].IsDestroy()
				&& !ObjectSpawner::GetInstance().GetBigEnemies()[j].IsDestroy())
			{
				ObjectSpawner::GetInstance().SpawnHitMarkers(Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].GetPos());
				ObjectSpawner::GetInstance().GetBigEnemies()[j].Damage(1);
				Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].Destroy();
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

	Texture::GetInstance().m_PlayerShip.HandleEvent(event);
}

void Game::Render()
{
	window.clear();
	Texture::GetInstance().m_PlayerShip.Render(window);
	ObjectSpawner::GetInstance().Render(window);
	Texture::GetInstance().Render(window);
	window.display();
}


void Game::Clean()
{
	window.cleanUp();
	SDL_Quit();
}