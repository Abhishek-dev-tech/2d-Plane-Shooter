#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int x, int y, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();
	SDL_Renderer* GetRenderer();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
#pragma once
