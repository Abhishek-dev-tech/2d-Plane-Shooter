#include "Texture.h"

Texture::Texture()
{
}

Texture& Texture::GetInstance()
{
	static Texture* instance = new Texture;

	return *instance;
}

void Texture::LoadTextures(RenderWindow window)
{
	playerShip = window.loadTexture("res/PlayerShip.png");
	projectile01 = window.loadTexture("res/Projectile01.png");

	smallEnemyShips[0] = window.loadTexture("res/SmallEnemyShip_1.png");
	smallEnemyShips[1] = window.loadTexture("res/SmallEnemyShip_2.png");
	smallEnemyShips[2] = window.loadTexture("res/SmallEnemyShip_3.png");

	mediumEnemyShips[0] = window.loadTexture("res/MediumEnemyShip_1.png");
	mediumEnemyShips[1] = window.loadTexture("res/MediumEnemyShip_2.png");
	mediumEnemyShips[2] = window.loadTexture("res/MediumEnemyShip_3.png");

	bigEnemyShips[0] = window.loadTexture("res/BigEnemyShip_1.png");
	bigEnemyShips[1] = window.loadTexture("res/BigEnemyShip_2.png");
	bigEnemyShips[2] = window.loadTexture("res/BigEnemyShip_3.png");

	hitMark[0] = window.loadTexture("res/HitMark_1.png");
	hitMark[1] = window.loadTexture("res/HitMark_2.png");
	hitMark[2] = window.loadTexture("res/HitMark_3.png");

	missile = window.loadTexture("res/Missile.png");
	blastEffect = window.loadTexture("res/BlastEffect.png");
	smokeEffect = window.loadTexture("res/SmokeEffect.png");

	cursor = window.loadTexture("res/Cursor.png");

	SetEntity();
}

void Texture::SetEntity()
{
	m_PlayerShip = Player(Vector2f(360, 650), playerShip, Vector2f(2, 2));

	m_Cursor = Entity(Vector2f(0, 0), cursor, Vector2f(2, 2));

	m_PlayerShip.GetTextures(projectile01);
	
}

void Texture::Update()
{
	m_PlayerShip.Update();
	m_Cursor.Update();
}

void Texture::Render(RenderWindow window)
{
	window.render(m_PlayerShip, 0);
	window.render(m_Cursor, 0);
}
