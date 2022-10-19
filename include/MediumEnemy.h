#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"


class MediumEnemy : public Entity
{
public:
	MediumEnemy() = default;
	MediumEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType);
	void Update();
	void GetTextures(SDL_Texture* p_EnemyProjectile);
	void Render(RenderWindow window);
	void Shoot(float p_bulletOffset, int p_bulletPair);
	void DefineShipType(int type);

private:
	float m_Speed;
	float m_OriginalFireRate;
	float m_CurrentFireRate;
	float previousTime;
	float m_BulletOffset;
	float m_ShootDelay;

	int counter;
	int m_bulletPair;
	int m_noOfBullets;

	enum ShipType
	{
		DoubleShooter_Slower,
		DoubleShooter_Faster,
		Faster
	};

	ShipType m_shipType;

	bool shootCoolDown;

	SDL_Texture* m_EnemyProjectile;

	std::vector<Projectile> projectiles;
};