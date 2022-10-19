#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"


class SmallEnemy : public Entity
{
public:
	SmallEnemy() = default;
	SmallEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType);
	void Update();
	void GetTextures(SDL_Texture* p_EnemyProjectile);
	void Render(RenderWindow window);
	void Shoot(float p_bulletOffset, int p_bulletPair);
	void DefineShipType(int type);

private:
	float m_Speed;
	float maxTime;
	float previousTime;
	float m_bulletOffset;

	int counter;
	int m_bulletPair;
	int m_noOfBullets;

	enum ShipType
	{
		SingleShooter,
		DoubleShooter,
		Faster
	};

	ShipType shipType;

	bool shootCoolDown;

	SDL_Texture* m_EnemyProjectile;

	std::vector<Projectile> projectiles;
};