#pragma once
#include <vector>
#include <iostream>

#include "Entity.h"
#include "RenderWindow.h"
#include "SmallEnemy.h"
#include "MediumEnemy.h"
#include "BigEnemy.h"


class ObjectSpawner
{
public:
	ObjectSpawner();
	void Update();
	void Render(RenderWindow window);
	void SpawnEnemies();
	void SpawnSmallEnemies(Vector2f p_pos);
	void SpawnMediumEnemies(Vector2f p_pos);
	void SpawnBigEnemies(Vector2f p_pos);
	void SpawnPartten();

	void GetTextures(SDL_Texture* p_SmallEnemyShip, 
		SDL_Texture* p_EnemyProjectile01, 
		SDL_Texture* p_MediumEnemyShip, 
		SDL_Texture* p_BigEnemyShip,
		SDL_Texture* p_Missile);

	void GetEntity(Entity* p_Player);

private:
	float maxTime;
	float previousTime;

	Vector2f StrightSpawnPositions[3] = {Vector2f(100, -20), Vector2f(600, -20) , Vector2f(350, -20)};

	std::vector<SmallEnemy> smallEnemies;
	std::vector<MediumEnemy> mediumEnemies;
	std::vector<BigEnemy> bigEnemies;

	SDL_Texture* m_SmallEnemyShip;
	SDL_Texture* m_MediumEnemyShip;
	SDL_Texture* m_BigEnemyShip;
	SDL_Texture* m_EnemyProjectile01;
	SDL_Texture* m_Missile;

	Entity* m_Player;

	bool once;
};