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
	BigEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale);
	void Update();
	void GetTextures(SDL_Texture* p_EnemyProjectile, SDL_Texture* p_Missile);
	void GetEntity(Entity* p_Player);
	void Render(RenderWindow window);
	void ShootBullets();
	void ShootMissiles();

private:
	float m_Speed;
	float maxTime;
	float previousTime;
	float missileAngle;

	int counter;
	int bulletOffset;

	bool shootCoolDown;
	bool missileCoolDown;

	SDL_Texture* m_EnemyProjectile;
	SDL_Texture* m_Missile;

	std::vector<Projectile> projectiles;
	std::vector<Missile> missiles;

	Entity* m_Player;
};