#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"

RenderWindow::RenderWindow(const char* p_title, int x, int y, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity, float angle)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.GetPos().x - src.w / 2 * p_entity.GetScale().x;
	dst.y = p_entity.GetPos().y - src.h / 2 * p_entity.GetScale().y;
	dst.w = p_entity.getCurrentFrame().w * p_entity.GetScale().x;
	dst.h = p_entity.getCurrentFrame().h * p_entity.GetScale().y;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, angle, NULL, SDL_FLIP_NONE);
}

void RenderWindow::display()
{
	SDL_SetRenderDrawColor(renderer, 223, 245, 245, 255);
	SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::GetRenderer()
{
	return renderer;
}