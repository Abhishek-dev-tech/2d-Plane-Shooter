#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Texture.h"
#include "RenderWindow.h"
#include "ObjectSpawner.h"


class Game
{
public:
	Game();

	void Init();
	void HandleEvent();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; }


private:
	bool isRunning;

	int mouseX;
	int mouseY;

	RenderWindow window;
	Texture texture;
	ObjectSpawner objectSpawner;
};