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

	Texture();

	static Texture& GetInstance();

	void LoadTextures(RenderWindow window);
	void Update();
	void SetEntity();
	void Render(RenderWindow window);

	Player m_PlayerShip;

	Entity m_CursorWhite;
	Entity m_CursorRed;

	SDL_Texture* projectile01;

	SDL_Texture* smallEnemyShips[3];
	SDL_Texture* mediumEnemyShips[3];
	SDL_Texture* bigEnemyShips[3];

	SDL_Texture* hitMark[3];

	SDL_Texture* missile;
	SDL_Texture* blastEffect;
	SDL_Texture* smokeEffect;

	SDL_Texture* flare;

	bool isCursorCollideWithEnemy;

private:
	SDL_Texture* playerShip;
	SDL_Texture* cursorWhite;
	SDL_Texture* cursorRed;

};
