#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"


class SmallEnemy : public Entity
{
public:
	SmallEnemy() = default;
	SmallEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale);
	void Update();
	void GetTextures(SDL_Texture* p_EnemyProjectile);
	void Render(RenderWindow window);
	void Shoot();

private:
	float m_Speed;
	float maxTime;
	float previousTime;

	int counter;

	bool shootCoolDown;

	SDL_Texture* m_EnemyProjectile;

	std::vector<Projectile> projectiles;
};