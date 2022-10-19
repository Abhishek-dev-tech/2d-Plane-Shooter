#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"
#include "Missile.h"


class BigEnemy : public Entity
{
public:
	BigEnemy() = default;
	BigEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType);
	void Update();
	void GetTextures(SDL_Texture* p_EnemyProjectile, SDL_Texture* p_Missile);
	void GetEntity(Entity* p_Player);
	void Render(RenderWindow window);
	void ShootBullets(float p_bulletOffset, int p_bulletPair);
	void ShootMissiles();
	void DefineShipType(int type);

private:
	float m_Speed;
	float m_OriginalFireRate;
	float m_CurrentFireRate;
	float previousTime;
	float missileAngle;
	float m_BulletOffset;
	float m_ShootDelay;


	int counter;
	int m_bulletPair;
	int m_noOfBullets;

	enum ShipType
	{
		QuardShooter_SingleMissile_Slower,
		QuardShooter_DoubleMissile_Faster,
		Faster
	};

	ShipType m_shipType;

	bool shootCoolDown;
	bool missileCoolDown;

	SDL_Texture* m_EnemyProjectile;
	SDL_Texture* m_Missile;

	std::vector<Projectile> projectiles;
	std::vector<Missile> missiles;

	Entity* m_Player;
};