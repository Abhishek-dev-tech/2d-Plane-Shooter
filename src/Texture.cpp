#include "Texture.h"

Texture::Texture()
{
}

void Texture::LoadTextures(RenderWindow window)
{
	playerShip = window.loadTexture("res/PlayerShip.png");

	SetEntity();
}

void Texture::SetEntity()
{
	m_PlayerShip = Entity(Vector2f(100, 100), playerShip, Vector2f(2, 2));

}

void Texture::Update()
{

}

void Texture::Render(RenderWindow window)
{
	window.render(m_PlayerShip);
}
