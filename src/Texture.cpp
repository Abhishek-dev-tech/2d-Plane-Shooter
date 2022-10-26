#include "Texture.h"

Texture::Texture()
{
	isCursorCollideWithEnemy = false;
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

	flare = window.loadTexture("res/Flare.png");

	firstAid = window.loadTexture("res/FirstAid.png");
	shield = window.loadTexture("res/Shield.png");

	cursorWhite = window.loadTexture("res/Cursor_White.png");
	cursorRed = window.loadTexture("res/Cursor_Red.png");

	square = window.loadTexture("res/UI/Square.png");

	font16 = TTF_OpenFont("res/Fonts/RifficFree-Bold.ttf", 16);
	font28 = TTF_OpenFont("res/Fonts/RifficFree-Bold.ttf", 26);

	SetEntity();
}

void Texture::SetEntity()
{
	m_PlayerShip = Player(Vector2f(360, 650), playerShip, Vector2f(2.25, 2.25));

	m_CursorWhite = Entity(Vector2f(0, 0), cursorWhite, Vector2f(2, 2));	
	m_CursorRed = Entity(Vector2f(0, 0), cursorRed, Vector2f(2, 2));	

	m_HealthBar = Entity(Vector2f(0, 0), square, Vector2f(1, 1));	
	m_MissileIcon = Entity(Vector2f(0, 0), missile, Vector2f(2, 2));
	m_FlareIcon = Entity(Vector2f(0, 0), flare, Vector2f(2, 2));
}

void Texture::Update()
{
	m_PlayerShip.Update();
	m_CursorWhite.Update();
	m_CursorRed.Update();
	m_HealthBar.Update();
}

void Texture::Render(RenderWindow window)
{
	if(!m_PlayerShip.IsDestroy())
		window.Render(m_PlayerShip, 0, false);

	if(isCursorCollideWithEnemy)
		window.Render(m_CursorRed, 0, false);
	else
		window.Render(m_CursorWhite, 0, false);
}
