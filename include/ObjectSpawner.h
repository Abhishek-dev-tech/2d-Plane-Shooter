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
	void RemoveEnemies();

	void SetTextures(SDL_Texture* p_SmallEnemyShips[],
		SDL_Texture* p_EnemyProjectile01, 
		SDL_Texture* p_MediumEnemyShips[],
		SDL_Texture* p_BigEnemyShips[],
		SDL_Texture* p_Missile);

	std::vector<SmallEnemy>& GetSmallEnemies();
	std::vector<MediumEnemy>& GetMediumEnemies();
	std::vector<BigEnemy>& GetBigEnemies();

	void SetEntity(Entity* p_Player);

private:
	float maxTime;
	float previousTime;

	int m_SmallEnemyCounter;
	int m_MediumEnemyCounter;
	int m_BigEnemyCounter;

	Vector2f StrightSpawnPositions;

	std::vector<SmallEnemy> smallEnemies;
	std::vector<MediumEnemy> mediumEnemies;
	std::vector<BigEnemy> bigEnemies;

	SDL_Texture* m_SmallEnemyShips[3];
	SDL_Texture* m_MediumEnemyShips[3];
	SDL_Texture* m_BigEnemyShips[3];
	SDL_Texture* m_EnemyProjectile01;
	SDL_Texture* m_Missile;

	Entity* m_Player;

};