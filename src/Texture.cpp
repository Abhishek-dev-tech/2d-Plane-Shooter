#include "Texture.h"

Texture::Texture()
{
}

void Texture::LoadTextures(RenderWindow window)
{
	playerShip = window.loadTexture("res/PlayerShip.png");
	playerProjectile01 = window.loadTexture("res/PlayeProjectile01.png");

	SetEntity();
}

void Texture::SetEntity()
{
	m_PlayerShip = Player(Vector2f(110, 110), playerShip, Vector2f(2, 2));

	m_PlayerShip.GetTextures(playerProjectile01);
}

void Texture::Update()
{
	m_PlayerShip.Update();
}

void Texture::Render(RenderWindow window)
{
	window.render(m_PlayerShip);
}
