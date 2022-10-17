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
}

void ObjectSpawner::SpawnEnemies()
{
	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime)
	{
		previousTime = SDL_GetTicks() * 0.001;
		SpawnSmallEnemies();
	}
}

void ObjectSpawner::SpawnSmallEnemies()
{
	SmallEnemy temp = SmallEnemy(Vector2f(200, -20), m_SmallEnemyShip, Vector2f(1.75, 1.75));
	temp.GetTextures(m_EnemyProjectile01);

	smallEnemies.push_back(temp);
}

void ObjectSpawner::GetTextures(SDL_Texture* p_SmallEnemyShip, SDL_Texture* p_EnemyProjectile01)
{
	m_SmallEnemyShip = p_SmallEnemyShip;
	m_EnemyProjectile01 = p_EnemyProjectile01;

}

void ObjectSpawner::Render(RenderWindow window)
{
	for (int i = 0; i < smallEnemies.size(); i++)
	{
		smallEnemies[i].Render(window);
		window.render(smallEnemies[i], 180);
	}
}