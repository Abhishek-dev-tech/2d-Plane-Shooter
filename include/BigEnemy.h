#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"
#include "Missile.h"
#include "Enemy.h"

class BigEnemy : public Enemy
{
public:
	BigEnemy() = default;
	BigEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType);
	void Update();
	void GetTextures(SDL_Texture* p_EnemyProjectile, SDL_Texture* p_Missile);
	void GetEntity(Entity* p_Player);
	void Render(RenderWindow window);
	void Shoot(float p_bulletOffset, int p_bulletPair);
	void ShootMissiles();
	void DefineShipType(int type);

private:

	float missileAngle;

	enum ShipType
	{
		QuardShooter_SingleMissile_Slower,
		QuardShooter_DoubleMissile_Faster,
		Faster
	};

	ShipType m_shipType;

	bool missileCoolDown;

	SDL_Texture* m_Missile;

	std::vector<Missile> missiles;

	Entity* m_Player;
};