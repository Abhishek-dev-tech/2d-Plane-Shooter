#pragma once
#include <vector>
#include <iostream>

#include "Entity.h"
#include "RenderWindow.h"
#include "SmallEnemy.h"


class ObjectSpawner
{
public:
	ObjectSpawner();
	void Update();
	void Render(RenderWindow window);
	void SpawnEnemies();
	void SpawnSmallEnemies();
	void GetTextures(SDL_Texture* p_SmallEnemyShip, SDL_Texture* p_EnemyProjectile01);

private:
	float maxTime;
	float previousTime;

	//Vector2f SpawnPositions[3] = {Vector2f(100, -20), Vector2f(600, -20) , Vector2f(350, -20)};

	std::vector<SmallEnemy> smallEnemies;

	SDL_Texture* m_SmallEnemyShip;
	SDL_Texture* m_EnemyProjectile01;
};