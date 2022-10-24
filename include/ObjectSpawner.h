#pragma once
#include <vector>
#include <iostream>

#include "Entity.h"
#include "RenderWindow.h"
#include "SmallEnemy.h"
#include "MediumEnemy.h"
#include "BigEnemy.h"
#include "Texture.h"


class ObjectSpawner
{
public:
	ObjectSpawner();

	static ObjectSpawner& GetInstance();

	void Update();
	void Render(RenderWindow& window);
	void SpawnEnemies();
	void SpawnSmallEnemies(Vector2f p_pos);
	void SpawnMediumEnemies(Vector2f p_pos);
	void SpawnBigEnemies(Vector2f p_pos);
	void SpawnPartten();
	void RemoveEnemies();
	void SpawnHitMarkers(Vector2f p_Pos);
	void SpawnBlastEffect(Vector2f p_Pos, Vector2f p_Scale);
	void SpawnSmokEffect(Vector2f p_Pos, Vector2f p_Scale);

	std::vector<SmallEnemy>& GetSmallEnemies();
	std::vector<MediumEnemy>& GetMediumEnemies();
	std::vector<BigEnemy>& GetBigEnemies();

	std::vector<Entity>& GetHitMarkers();

private:
	float maxTime;
	float previousTime;

	Vector2f StrightSpawnPositions;

	std::vector<SmallEnemy> smallEnemies;
	std::vector<MediumEnemy> mediumEnemies;
	std::vector<BigEnemy> bigEnemies;

	std::vector<Entity> hitMarkers;
	std::vector<Entity> blastEffect;
	std::vector<Entity> smokeEffect;

};