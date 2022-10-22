#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"
#include "Missile.h"


class Player : public Entity
{
public:
	Player() = default;
	Player(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale);
	void Update();
	void HandleEvent(SDL_Event event);
	void Render(RenderWindow window);
	void Shoot();
	void ShootMissile();
	void RemoveProjectiles();

	std::vector<Projectile>& GetPlayerProjectiles();

private:
	float m_Speed;
	float maxTime; 
	float previousTime;

	bool shootCoolDown;

	std::vector<Projectile> projectiles;
	std::vector<Missile> missiles;
};
