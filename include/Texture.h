#pragma once
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"

class Texture
{
public:

	Entity m_PlayerShip;

	Texture();

	void LoadTextures(RenderWindow window);
	void Update();
	void SetEntity();
	void Render(RenderWindow window);

private:
	SDL_Texture* playerShip;
};
