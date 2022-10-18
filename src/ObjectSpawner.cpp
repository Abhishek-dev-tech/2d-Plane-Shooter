#include"ObjectSpawner.h"


ObjectSpawner::ObjectSpawner()
{
	previousTime = 0;
	maxTime = 4;
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
}

void ObjectSpawner::SpawnEnemies()
{
	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime)
	{
		previousTime = SDL_GetTicks() * 0.001;
		//SpawnSmallEnemies(Vector2f(200, -20));
		//SpawnMediumEnemies(Vector2f(400, -20));
		SpawnBigEnemies(Vector2f(600, -20));
		//SpawnPartten();
	}
}

void ObjectSpawner::SpawnSmallEnemies(Vector2f p_pos)
{
	SmallEnemy temp = SmallEnemy(p_pos, m_SmallEnemyShip, Vector2f(1.75, 1.75));
	temp.GetTextures(m_EnemyProjectile01);

	smallEnemies.push_back(temp);
}

void ObjectSpawner::SpawnMediumEnemies(Vector2f p_pos)
{
	MediumEnemy temp = MediumEnemy(p_pos, m_MediumEnemyShip, Vector2f(1.9, 1.9));
	temp.GetTextures(m_EnemyProjectile01);

	mediumEnemies.push_back(temp);
}

void ObjectSpawner::SpawnBigEnemies(Vector2f p_pos)
{
	BigEnemy temp = BigEnemy(p_pos, m_BigEnemyShip, Vector2f(2.2, 2.2));
	temp.GetTextures(m_EnemyProjectile01);

	bigEnemies.push_back(temp);
}

void ObjectSpawner::SpawnPartten()
{
	SpawnBigEnemies(Vector2f(400, -10));
	SpawnSmallEnemies(Vector2f(350, -5));
	SpawnSmallEnemies(Vector2f(450, -5));
}

void ObjectSpawner::GetTextures(SDL_Texture* p_SmallEnemyShip, SDL_Texture* p_EnemyProjectile01, SDL_Texture* p_MediumEnemyShip, SDL_Texture* p_BigEnemyShip)
{
	m_SmallEnemyShip = p_SmallEnemyShip;
	m_EnemyProjectile01 = p_EnemyProjectile01;
	m_MediumEnemyShip = p_MediumEnemyShip;
	m_BigEnemyShip = p_BigEnemyShip;
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
	
	for (int i = 0; i < bigEnemies.size(); i++)
	{
		bigEnemies[i].Render(window);
		window.render(bigEnemies[i], 180);
	}
}