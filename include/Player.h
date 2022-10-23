#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"
#include "Missile.h"
#include "Timer.h"


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
	Missile& GetMissile();

	bool once;
	bool missileCoolDown;


private:
	float m_Speed;
	float maxTime; 
	float previousTime;	
	float m_MissileMaxTime;
	float missileAngle;

	bool shootCoolDown;

	Vector2f* m_Target;

	std::vector<Projectile> projectiles;

	Missile missile;

	Timer m_MissileTimer;
};
