#include "Game.h"
#include "RenderWindow.h"
#include "Collision.h"
#include "AudioManager.h"

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

	TTF_Init();

	SDL_ShowCursor(SDL_DISABLE);

	Texture::GetInstance().LoadTextures(window);
	AudioManager::GetInstance().Init();
	UIManager::GetInstance().SetRenderer(window.GetRenderer());
}

void Game::Update()
{
	if (!UIManager::GetInstance().m_Exit)
		isRunning = true;
	else
		isRunning = false;

	SDL_GetMouseState(&mouseX, &mouseY);
	Texture::GetInstance().m_CursorWhite.SetPos(Vector2f(mouseX, mouseY));
	Texture::GetInstance().m_CursorRed.SetPos(Vector2f(mouseX, mouseY));

	Texture::GetInstance().Update();

	ObjectSpawner::GetInstance().Update();

	UIManager::GetInstance().Update();

	CheckCollision();

	srand(SDL_GetTicks());
}

void Game::CheckCollision()
{
	std::vector<Enemy*> allEnemies;

	for (int i = 0; i < ObjectSpawner::GetInstance().GetSmallEnemies().size(); i++)
		allEnemies.push_back(&ObjectSpawner::GetInstance().GetSmallEnemies()[i]);

	for (int i = 0; i < ObjectSpawner::GetInstance().GetMediumEnemies().size(); i++)
		allEnemies.push_back(&ObjectSpawner::GetInstance().GetMediumEnemies()[i]);

	for (int i = 0; i < ObjectSpawner::GetInstance().GetBigEnemies().size(); i++)
		allEnemies.push_back(&ObjectSpawner::GetInstance().GetBigEnemies()[i]);
	
	//Collosion between FirstAid and player 
	if (Collision::IsCollide(&Texture::GetInstance().m_PlayerShip.GetDst(), &ObjectSpawner::GetInstance().GetFirstAid().GetDst())
		&& !ObjectSpawner::GetInstance().GetFirstAid().IsDestroy()
		&& !Texture::GetInstance().m_PlayerShip.IsDestroy())
	{
		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_FirstAid);
		Texture::GetInstance().m_PlayerShip.SetHitPoints(50);
		UIManager::GetInstance().ResetHealthBar();
		ObjectSpawner::GetInstance().GetFirstAid().Destroy();
	}

	//Collosion between Shield and player 
	if (Collision::IsCollide(&Texture::GetInstance().m_PlayerShip.GetDst(), &ObjectSpawner::GetInstance().GetShield().GetDst())
		&& !ObjectSpawner::GetInstance().GetShield().IsDestroy()
		&& !Texture::GetInstance().m_PlayerShip.IsDestroy())
	{
		AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Shield);
		Texture::GetInstance().m_PlayerShip.SetShield(20);
		UIManager::GetInstance().ResetShieldBar();
		ObjectSpawner::GetInstance().GetShield().Destroy();
	}
		
	

	//Collosion between enemy and player missile
	for (int i = 0; i < allEnemies.size(); i++)
	{
		if (Collision::IsCollide(&Texture::GetInstance().m_PlayerShip.GetMissile().GetDst(), &allEnemies[i]->GetDst())
			&& !Texture::GetInstance().m_PlayerShip.GetMissile().IsDestroy())
		{
			Texture::GetInstance().m_PlayerShip.GetMissile().Destroy();
			allEnemies[i]->Damage(15);
			ObjectSpawner::GetInstance().SpawnBlastEffect(Texture::GetInstance().m_PlayerShip.GetMissile().GetPos(), Vector2f(5, 5));
			ObjectSpawner::GetInstance().SpawnSmokEffect(Texture::GetInstance().m_PlayerShip.GetMissile().GetPos(), Vector2f(5, 5));
		}
	}

	//Collosion between enemy and cursor 
	for (int j = 0; j < allEnemies.size(); j++)
	{
		if (Collision::IsCollide(&Texture::GetInstance().m_CursorWhite.GetDst(), &allEnemies[j]->GetDst()))
		{
			Texture::GetInstance().isCursorCollideWithEnemy = true;

			if (mouseButtonDown && Texture::GetInstance().m_PlayerShip.missileCoolDown && Texture::GetInstance().m_PlayerShip.once)
			{
				Texture::GetInstance().m_PlayerShip.SetPlayerMissileTarget(&allEnemies[j]->GetPos());
				Texture::GetInstance().m_PlayerShip.once = false;

			}

			break;
	    }
		else
			Texture::GetInstance().isCursorCollideWithEnemy = false;
	}
	

	//Collosion between enemy missile and player
	for (int i = 0; i < ObjectSpawner::GetInstance().GetBigEnemies().size(); i++)
	{
		if (Collision::IsCollide(&Texture::GetInstance().m_PlayerShip.GetDst(), &ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().GetDst())
			&& !ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().IsDestroy()
			&& !Texture::GetInstance().m_PlayerShip.IsDestroy())
		{
			ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().Destroy();
			Texture::GetInstance().m_PlayerShip.Damage(5);
			AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Explosion);
			ObjectSpawner::GetInstance().SpawnBlastEffect(ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().GetPos(), Vector2f(5, 5));
			ObjectSpawner::GetInstance().SpawnSmokEffect(ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().GetPos(), Vector2f(5, 5));
		}

		for (int j = 0; j < Texture::GetInstance().m_PlayerShip.GetFlares().size(); j++)
		{
			if (Collision::IsCollide(&Texture::GetInstance().m_PlayerShip.GetFlares()[j].GetDst(), &ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().GetDst())
				&& !ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().IsDestroy())
			{
				ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().Destroy();
				Texture::GetInstance().m_PlayerShip.GetFlares()[j].Destroy();
				AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_Explosion);
				ObjectSpawner::GetInstance().SpawnBlastEffect(ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().GetPos(), Vector2f(5, 5));
				ObjectSpawner::GetInstance().SpawnSmokEffect(ObjectSpawner::GetInstance().GetBigEnemies()[i].GetMissiles().GetPos(), Vector2f(5, 5));
			}
		}
	}

	//Collosion between enemy bullets and player 
	for (int i = 0; i < allEnemies.size(); i++)
	{
		for (int j = 0; j < allEnemies[i]->GetProjectiles().size(); j++)
		{
			if (Collision::IsCollide(&Texture::GetInstance().m_PlayerShip.GetDst(), &allEnemies[i]->GetProjectiles()[j].GetDst())
				&& !allEnemies[i]->GetProjectiles()[j].IsDestroy()
				&& !Texture::GetInstance().m_PlayerShip.IsDestroy())
			{
				AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_BulletCollision);
				ObjectSpawner::GetInstance().SpawnHitMarkers(allEnemies[i]->GetProjectiles()[j].GetPos());
				Texture::GetInstance().m_PlayerShip.Damage(1);
				allEnemies[i]->GetProjectiles()[j].Destroy();
			}
		}
	}

	//Collosion between enemy and player bullets
	for (int i = 0; i < Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles().size(); i++)
	{
		for (int j = 0; j < allEnemies.size(); j++)
		{
			if (Collision::IsCollide(&Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].GetDst(), &allEnemies[j]->GetDst())
				&& !Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].IsDestroy()
				&& !allEnemies[j]->IsDestroy())
			{
				AudioManager::GetInstance().PlaySoundEffect(AudioManager::GetInstance().m_BulletCollision);
				ObjectSpawner::GetInstance().SpawnHitMarkers(Texture::GetInstance().m_PlayerShip.GetPlayerProjectiles()[i].GetPos());
				allEnemies[j]->Damage(1);
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

	if (event.type == SDL_MOUSEBUTTONDOWN)
		mouseButtonDown = true;
	else if(event.type == SDL_MOUSEBUTTONUP)
		mouseButtonDown = false;

	if (UIManager::GetInstance().m_gameState == UIManager::GetInstance().Playing)
		Texture::GetInstance().m_PlayerShip.HandleEvent(event);

	UIManager::GetInstance().HandleEvent(event);
}

void Game::Render()
{
	window.clear();

	if (UIManager::GetInstance().m_gameState != UIManager::GetInstance().Menu)
	{
		Texture::GetInstance().m_PlayerShip.Render(window);
		ObjectSpawner::GetInstance().Render(window);
	}

	UIManager::GetInstance().Render(window);

	Texture::GetInstance().Render(window);


	window.display();
}


void Game::Clean()
{
	TTF_CloseFont(Texture::GetInstance().font16);
	TTF_CloseFont(Texture::GetInstance().font28);
	window.cleanUp();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}