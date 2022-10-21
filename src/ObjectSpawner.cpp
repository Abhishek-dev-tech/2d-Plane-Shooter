#include"ObjectSpawner.h"


ObjectSpawner::ObjectSpawner()
{
	previousTime = 0;
	maxTime = 4;

	StrightSpawnPositions = Vector2f(50, -10);
}

ObjectSpawner& ObjectSpawner::GetInstance()
{
	static ObjectSpawner* instance = new ObjectSpawner;

	return *instance;
}

void ObjectSpawner::Update()
{
	SpawnEnemies();

	RemoveEnemies();


	for (int i = 0; i < smallEnemies.size(); i++)
		smallEnemies[i].Update();

	for (int i = 0; i < mediumEnemies.size(); i++)
		mediumEnemies[i].Update();

	for (int i = 0; i < bigEnemies.size(); i++)
		bigEnemies[i].Update();

	for (int i = 0; i < hitMarkers.size(); i++)
	{
		hitMarkers[i].SetScale(Vector2f(Mathf::Lerp(hitMarkers[i].GetScale().x, -0.05, 0.05), Mathf::Lerp(hitMarkers[i].GetScale().y, -0.05, 0.05)));
		
		if (hitMarkers[i].GetScale().x <= 0)
			hitMarkers.erase(hitMarkers.begin() + i);
	}

	for (int i = 0; i < blastEffect.size(); i++)
	{
		blastEffect[i].SetScale(Vector2f(Mathf::Lerp(blastEffect[i].GetScale().x, -0.05, 0.05), Mathf::Lerp(blastEffect[i].GetScale().y, -0.05, 0.05)));

		if (blastEffect[i].GetScale().x <= 0)
			blastEffect.erase(blastEffect.begin() + i);
	}

	for (int i = 0; i < smokeEffect.size(); i++)
	{
		smokeEffect[i].SetScale(Vector2f(Mathf::Lerp(smokeEffect[i].GetScale().x, -0.05, 0.0075), Mathf::Lerp(smokeEffect[i].GetScale().y, -0.05, 0.0075)));

		if (smokeEffect[i].GetScale().x <= 0)
			smokeEffect.erase(smokeEffect.begin() + i);
	}


}

void ObjectSpawner::SpawnEnemies()
{
	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime)
	{
		previousTime = SDL_GetTicks() * 0.001;

		int rand = Mathf::Random(1, 100);
		
		if (rand <= 50)
			SpawnSmallEnemies(Vector2f(Mathf::Random(50, 650), -10));

		else if (rand <= 90 && rand > 50)
			SpawnMediumEnemies(Vector2f(Mathf::Random(50, 650), -10));

		else if (rand <= 95 && rand > 90)
			SpawnBigEnemies(Vector2f(Mathf::Random(50, 650), -10));
		else
			SpawnPartten();

	}
}

void ObjectSpawner::SpawnSmallEnemies(Vector2f p_pos)
{
	int rand = Mathf::Random(1, 3);
	SmallEnemy temp = SmallEnemy(p_pos, Texture::GetInstance().smallEnemyShips[rand - 1], Vector2f(1.75, 1.75), rand);

	smallEnemies.push_back(temp);

}

void ObjectSpawner::SpawnMediumEnemies(Vector2f p_pos)
{
	int rand = Mathf::Random(1, 3);
	MediumEnemy temp = MediumEnemy(p_pos, Texture::GetInstance().mediumEnemyShips[rand - 1], Vector2f(1.9, 1.9), rand);

	mediumEnemies.push_back(temp);

}

void ObjectSpawner::SpawnBigEnemies(Vector2f p_pos)
{
	int rand = Mathf::Random(1, 3);
	BigEnemy temp = BigEnemy(p_pos, Texture::GetInstance().bigEnemyShips[rand - 1], Vector2f(2.2, 2.2), rand);

	bigEnemies.push_back(temp);
}

void ObjectSpawner::SpawnHitMarkers(Vector2f p_Pos)
{
	Entity temp = Entity(p_Pos, Texture::GetInstance().hitMark[Mathf::Random(0, 2)], Vector2f(2, 2));

	hitMarkers.push_back(temp);
}

void ObjectSpawner::SpawnBlastEffect(Vector2f p_Pos, Vector2f p_Scale)
{
	Entity temp = Entity(p_Pos, Texture::GetInstance().blastEffect, p_Scale);

	blastEffect.push_back(temp);
}

void ObjectSpawner::SpawnSmokEffect(Vector2f p_Pos, Vector2f p_Scale)
{
	Entity temp = Entity(p_Pos, Texture::GetInstance().smokeEffect, p_Scale);

	smokeEffect.push_back(temp);
}

void ObjectSpawner::SpawnPartten()
{
	int rand = Mathf::Random(150, 600);

	SpawnBigEnemies(Vector2f(rand, -20));
	SpawnSmallEnemies(Vector2f(rand + 80, -10));
	SpawnSmallEnemies(Vector2f(rand - 80, -10));
}

void ObjectSpawner::RemoveEnemies()
{

	for (int i = 0; i < smallEnemies.size(); i++)
		if (smallEnemies[i].IsDestroy() && smallEnemies[i].GetProjectiles().empty())
			smallEnemies.erase(smallEnemies.begin() + i);

	for (int i = 0; i < mediumEnemies.size(); i++)
		if (mediumEnemies[i].IsDestroy() && mediumEnemies[i].GetProjectiles().empty())
			mediumEnemies.erase(mediumEnemies.begin() + i);
	
	for (int i = 0; i < bigEnemies.size(); i++)
		if (bigEnemies[i].IsDestroy() && bigEnemies[i].GetProjectiles().empty() && bigEnemies[i].GetMissiles().empty())
			bigEnemies.erase(bigEnemies.begin() + i);
		
	
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

std::vector<Entity>& ObjectSpawner::GetHitMarkers()
{
	return hitMarkers;
}

void ObjectSpawner::Render(RenderWindow window)
{

	for (int i = 0; i < smallEnemies.size(); i++)
	{
		smallEnemies[i].Render(window);

		if (!smallEnemies[i].IsDestroy())
			window.render(smallEnemies[i], 180);
		
	}

	for (int i = 0; i < mediumEnemies.size(); i++)
	{
		mediumEnemies[i].Render(window);

		if (!mediumEnemies[i].IsDestroy())
			window.render(mediumEnemies[i], 180);
		
	}	
	
	for (int i = 0; i < bigEnemies.size(); i++)
	{
		bigEnemies[i].Render(window);

		if (!bigEnemies[i].IsDestroy())
			window.render(bigEnemies[i], 180);
		
	}

	for (int i = 0; i < hitMarkers.size(); i++)
		window.render(hitMarkers[i], 0);

	for (int i = 0; i < smokeEffect.size(); i++)
		window.render(smokeEffect[i], 0);
	
	for (int i = 0; i < blastEffect.size(); i++)
		window.render(blastEffect[i], 0);	
}