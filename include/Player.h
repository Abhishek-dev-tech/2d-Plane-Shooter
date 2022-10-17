#pragma once
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Projectile.h"


class Player : public Entity
{
public:
	Player() = default;
	Player(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale);
	void Update();
	void HandleEvent(SDL_Event event);
	void GetTextures(SDL_Texture* p_PlayerProjectile01);
	void Render(RenderWindow window);
	void Shoot();

private:
	float m_Speed;
	float maxTime; 
	float previousTime;


	bool shootCoolDown;

	SDL_Texture* m_PlayerProjectile01;

	std::vector<Projectile> projectiles;
};
