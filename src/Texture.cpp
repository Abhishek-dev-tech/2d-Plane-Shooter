#include "Texture.h"

Texture::Texture()
{
}

void Texture::LoadTextures(RenderWindow window)
{
	playerShip = window.loadTexture("res/PlayerShip.png");
	projectile01 = window.loadTexture("res/Projectile01.png");

	smallEnemyShips[0] = window.loadTexture("res/SmallEnemyShip_1.png");
	smallEnemyShips[1] = window.loadTexture("res/SmallEnemyShip_2.png");
	smallEnemyShips[2] = window.loadTexture("res/SmallEnemyShip_3.png");

	mediumEnemyShip = window.loadTexture("res/MediumEnemyShip.png");
	bigEnemyShip = window.loadTexture("res/BigEnemyShip.png");
	missile = window.loadTexture("res/Missile.png");

	SetEntity();
}

void Texture::SetEntity()
{
	m_PlayerShip = Player(Vector2f(360, 650), playerShip, Vector2f(2, 2));

	m_PlayerShip.GetTextures(projectile01);
}

void Texture::Update()
{
	m_PlayerShip.Update();
}

void Texture::Render(RenderWindow window)
{
	window.render(m_PlayerShip, 0);
}
