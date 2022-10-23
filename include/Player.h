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
	void SetPlayerMissileTarget(Vector2f* p_Target);

	std::vector<Projectile>& GetPlayerProjectiles();

private:
	float m_Speed;
	float maxTime; 
	float previousTime;	
	float missileCoolDownMaxTime;
	float missileCoolDownPreviousTime;
	float missileAngle;

	bool shootCoolDown;
	bool missileCoolDown;

	Vector2f* m_Target;

	std::vector<Projectile> projectiles;
	Missile missile;
};
