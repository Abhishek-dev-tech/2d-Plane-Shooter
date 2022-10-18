#include"ObjectSpawner.h"


ObjectSpawner::ObjectSpawner()
{
	previousTime = 0;
	maxTime = 2;
}

void ObjectSpawner::Update()
{
	SpawnEnemies();

	for (int i = 0; i < smallEnemies.size(); i++)
		smallEnemies[i].Update();

	for (int i = 0; i < mediumEnemies.size(); i++)
		mediumEnemies[i].Update();
}

void ObjectSpawner::SpawnEnemies()
{
	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime)
	{
		previousTime = SDL_GetTicks() * 0.001;
		//SpawnSmallEnemies();
		SpawnMediumEnemies();
	}
}

void ObjectSpawner::SpawnSmallEnemies()
{
	SmallEnemy temp = SmallEnemy(Vector2f(200, -20), m_SmallEnemyShip, Vector2f(1.75, 1.75));
	temp.GetTextures(m_EnemyProjectile01);

	smallEnemies.push_back(temp);
}

void ObjectSpawner::SpawnMediumEnemies()
{
	MediumEnemy temp = MediumEnemy(Vector2f(400, -20), m_MediumEnemyShip, Vector2f(1.9, 1.9));
	temp.GetTextures(m_EnemyProjectile01);

	mediumEnemies.push_back(temp);
}

void ObjectSpawner::GetTextures(SDL_Texture* p_SmallEnemyShip, SDL_Texture* p_EnemyProjectile01, SDL_Texture* p_MediumEnemyShip)
{
	m_SmallEnemyShip = p_SmallEnemyShip;
	m_EnemyProjectile01 = p_EnemyProjectile01;
	m_MediumEnemyShip = p_MediumEnemyShip;
}

void ObjectSpawner::Render(RenderWindow window)
{
	for (int i = 0; i < smallEnemies.size(); i++)
	{
		smallEnemies[i].Render(window);

		window.render(smallEnemies[i], 180);
	}

	for (int i = 0; i < mediumEnemies.size(); i++)
	{
		mediumEnemies[i].Render(window);
		window.render(mediumEnemies[i], 180);
	}
}