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

	SDL_Texture* projectile01;

	SDL_Texture* smallEnemyShips[3];
	SDL_Texture* mediumEnemyShips[3];
	SDL_Texture* bigEnemyShips[3];

	SDL_Texture* missile;

	Texture();

	void LoadTextures(RenderWindow window);
	void Update();
	void SetEntity();
	void Render(RenderWindow window);

private:
	SDL_Texture* playerShip;

};
