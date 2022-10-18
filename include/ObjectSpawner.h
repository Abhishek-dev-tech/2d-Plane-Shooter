#pragma once
#include <vector>
#include <iostream>

#include "Entity.h"
#include "RenderWindow.h"
#include "SmallEnemy.h"
#include "MediumEnemy.h"


class ObjectSpawner
{
public:
	ObjectSpawner();
	void Update();
	void Render(RenderWindow window);
	void SpawnEnemies();
	void SpawnSmallEnemies();
	void SpawnMediumEnemies();

	void GetTextures(SDL_Texture* p_SmallEnemyShip, 
		SDL_Texture* p_EnemyProjectile01, 
		SDL_Texture* p_MediumEnemyShip);

private:
	float maxTime;
	float previousTime;

	Vector2f StrightSpawnPositions[3] = {Vector2f(100, -20), Vector2f(600, -20) , Vector2f(350, -20)};

	std::vector<SmallEnemy> smallEnemies;
	std::vector<MediumEnemy> mediumEnemies;

	SDL_Texture* m_SmallEnemyShip;
	SDL_Texture* m_MediumEnemyShip;
	SDL_Texture* m_EnemyProjectile01;
};