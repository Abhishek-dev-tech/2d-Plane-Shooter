#pragma once
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"

class Texture
{
public:

	Player m_PlayerShip;

	SDL_Texture* playerProjectile01;
	SDL_Texture* smallEnemyShip;
	SDL_Texture* mediumEnemyShip;
	SDL_Texture* bigEnemyShip;

	Texture();

	void LoadTextures(RenderWindow window);
	void Update();
	void SetEntity();
	void Render(RenderWindow window);

private:
	SDL_Texture* playerShip;

};
