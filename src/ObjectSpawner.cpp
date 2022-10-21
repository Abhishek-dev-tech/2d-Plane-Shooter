#include"ObjectSpawner.h"


ObjectSpawner::ObjectSpawner()
{
	previousTime = 0;
	maxTime = 4;

	m_SmallEnemyCounter = 1;
	m_MediumEnemyCounter = 1;
	m_BigEnemyCounter = 1;

	StrightSpawnPositions = Vector2f(50, -10);
}

void ObjectSpawner::Update()
{
	SpawnEnemies();

	for (int i = 0; i < smallEnemies.size(); i++)
		smallEnemies[i].Update();

	for (int i = 0; i < mediumEnemies.size(); i++)
		mediumEnemies[i].Update();

	for (int i = 0; i < bigEnemies.size(); i++)
		bigEnemies[i].Update();

	RemoveEnemies();

}

void ObjectSpawner::SpawnEnemies()
{
	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime)
	{
		previousTime = SDL_GetTicks() * 0.001;

		int rand = Mathf::Random(1, 100);
		
		if(rand <= 50)
			SpawnSmallEnemies(Vector2f(Mathf::Random(50, 650), -10));

		else if(rand <= 90 && rand > 50)
			SpawnMediumEnemies(Vector2f(Mathf::Random(50, 650), -10));
		
		else
			SpawnBigEnemies(Vector2f(Mathf::Random(50, 650), -10));
		//SpawnPartten();
	}
}

void ObjectSpawner::SpawnSmallEnemies(Vector2f p_pos)
{
	SmallEnemy temp = SmallEnemy(p_pos, m_SmallEnemyShips[m_SmallEnemyCounter - 1], Vector2f(1.75, 1.75), m_SmallEnemyCounter);
	temp.GetTextures(m_EnemyProjectile01);

	smallEnemies.push_back(temp);

	m_SmallEnemyCounter++;

	if (m_SmallEnemyCounter >= 4)
		m_SmallEnemyCounter = 1;
}

void ObjectSpawner::SpawnMediumEnemies(Vector2f p_pos)
{
	MediumEnemy temp = MediumEnemy(p_pos, m_MediumEnemyShips[m_MediumEnemyCounter - 1], Vector2f(1.9, 1.9), m_MediumEnemyCounter);
	temp.GetTextures(m_EnemyProjectile01);

	mediumEnemies.push_back(temp);

	m_MediumEnemyCounter++;

		
	if (m_MediumEnemyCounter >= 4)
		m_MediumEnemyCounter = 1;
}

void ObjectSpawner::SpawnBigEnemies(Vector2f p_pos)
{
	BigEnemy temp = BigEnemy(p_pos, m_BigEnemyShips[m_BigEnemyCounter - 1], Vector2f(2.2, 2.2), m_BigEnemyCounter);
	temp.SetTextures(m_EnemyProjectile01, m_Missile);
	temp.SetEntity(m_Player);

	bigEnemies.push_back(temp);

	m_BigEnemyCounter++;

	if (m_BigEnemyCounter >= 4)
		m_BigEnemyCounter = 1;
}

void ObjectSpawner::SpawnPartten()
{
	SpawnBigEnemies(Vector2f(400, -10));
	SpawnSmallEnemies(Vector2f(350, -5));
	SpawnSmallEnemies(Vector2f(450, -5));
}

void ObjectSpawner::SetTextures(SDL_Texture* p_SmallEnemyShips[], SDL_Texture* p_EnemyProjectile01, SDL_Texture* p_MediumEnemyShips[], SDL_Texture* p_BigEnemyShips[], SDL_Texture* p_Missile)
{
	for (int i = 0; i < 3; i++)
	{
		m_SmallEnemyShips[i] = p_SmallEnemyShips[i];
		m_MediumEnemyShips[i] = p_MediumEnemyShips[i];
		m_BigEnemyShips[i] = p_BigEnemyShips[i];
	}
	
	m_EnemyProjectile01 = p_EnemyProjectile01;
	m_Missile = p_Missile;
}

void ObjectSpawner::RemoveEnemies()
{

	for (int i = 0; i < smallEnemies.size(); i++)
	{
		if (smallEnemies[i].IsDestroy() && smallEnemies[i].GetProjectiles().empty())
			smallEnemies.erase(smallEnemies.begin() + i);

		for (int j = 0; j < smallEnemies[i].GetProjectiles().size(); j++)
		{
			if (smallEnemies[i].GetProjectiles()[j].GetPos().y >= 730)
				smallEnemies[i].GetProjectiles()[j].Destroy();
		}
	}
		

	for (int i = 0; i < mediumEnemies.size(); i++)
	{
		if (mediumEnemies[i].IsDestroy() && mediumEnemies[i].GetProjectiles().empty())
			mediumEnemies.erase(mediumEnemies.begin() + i);

		for (int j = 0; j < mediumEnemies[i].GetProjectiles().size(); j++)
		{
			if (mediumEnemies[i].GetProjectiles()[j].GetPos().y >= 730)
				mediumEnemies[i].GetProjectiles()[j].Destroy();
		}
	}
		

	for (int i = 0; i < bigEnemies.size(); i++)
	{
		if (bigEnemies[i].IsDestroy() && bigEnemies[i].GetProjectiles().empty())
			bigEnemies.erase(bigEnemies.begin() + i);

		for (int j = 0; j < bigEnemies[i].GetProjectiles().size(); j++)
		{
			if (bigEnemies[i].GetProjectiles()[j].GetPos().y >= 730)
				bigEnemies[i].GetProjectiles()[j].Destroy();
		}
	}	
	
}

void ObjectSpawner::SetEntity(Entity* p_Player)
{
	m_Player = p_Player;
}

std::vector<SmallEnemy>& ObjectSpawner::GetSmallEnemies()
{
	return smallEnemies;
}

std::vector<MediumEnemy>& ObjectSpawner::GetMediumEnemies()
{
	return mediumEnemies;
}

std::vector<BigEnemy>& ObjectSpawner::GetBigEnemies()
{
	return bigEnemies;
}

void ObjectSpawner::Render(RenderWindow window)
{
	for (int i = 0; i < smallEnemies.size(); i++)
	{
		smallEnemies[i].Render(window);

		//if (!smallEnemies[i].IsDestroy())
			window.render(smallEnemies[i], 180);
		
	}

	for (int i = 0; i < mediumEnemies.size(); i++)
	{
		mediumEnemies[i].Render(window);

		//if (!mediumEnemies[i].IsDestroy())
			window.render(mediumEnemies[i], 180);
		
	}	
	
	for (int i = 0; i < bigEnemies.size(); i++)
	{
		bigEnemies[i].Render(window);

		//if (!bigEnemies[i].IsDestroy())
			window.render(bigEnemies[i], 180);
		
	}
}