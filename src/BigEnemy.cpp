#include "BigEnemy.h"

BigEnemy::BigEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 0.4;

	previousTime = 0;
	maxTime = 0.1;
	missileAngle = 180;

	counter = 0;
	bulletOffset = 14;

	shootCoolDown = false;
	missileCoolDown = false;
}

void BigEnemy::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(1);

	for (int i = 0; i < missiles.size(); i++)
		missiles[i].Update(m_Player->GetPos());

	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime && shootCoolDown)
	{
		previousTime = SDL_GetTicks() * 0.001;
		shootCoolDown = false;

		if (counter == 7)
		{
			maxTime = 3.5;
			ShootMissiles();
			counter = 0;
		}
		else if (counter < 7)
			maxTime = 0.1;
	}



	ShootBullets();

	SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

}

void BigEnemy::ShootBullets()
{
	if (shootCoolDown)
		return;

	shootCoolDown = true;
	counter++;

	Projectile temp1 = Projectile(Vector2f(GetPos().x + bulletOffset + 8, GetPos().y), m_EnemyProjectile, Vector2f(0.9, 0.9));
	Projectile temp2 = Projectile(Vector2f(GetPos().x + bulletOffset, GetPos().y), m_EnemyProjectile, Vector2f(0.9, 0.9));

	Projectile temp3 = Projectile(Vector2f(GetPos().x - bulletOffset - 8, GetPos().y), m_EnemyProjectile, Vector2f(0.9, 0.9));
	Projectile temp4 = Projectile(Vector2f(GetPos().x - bulletOffset, GetPos().y), m_EnemyProjectile, Vector2f(0.9, 0.9));

	projectiles.push_back(temp1);
	projectiles.push_back(temp2);
	projectiles.push_back(temp3);
	projectiles.push_back(temp4);
}

void BigEnemy::ShootMissiles()
{
	if (missileCoolDown)
		return;

	missileCoolDown = true;

	Missile temp = Missile(Vector2f(GetPos().x, GetPos().y), m_Missile, Vector2f(2, 2));

	missiles.push_back(temp);
}

void BigEnemy::GetTextures(SDL_Texture* p_EnemyProjectile, SDL_Texture* p_Missile)
{
	m_EnemyProjectile = p_EnemyProjectile;
	m_Missile = p_Missile;
}

void BigEnemy::GetEntity(Entity* p_Player)
{
	m_Player = p_Player;
}

void BigEnemy::Render(RenderWindow window) {

	for (int i = 0; i < projectiles.size(); i++)
		window.render(projectiles[i], 0);
	
	for (int i = 0; i < missiles.size(); i++)
	{
		missileAngle = (float)std::atan2(m_Player->GetPos().y - missiles[i].GetPos().y, m_Player->GetPos().x - missiles[i].GetPos().x) * 180.0f / 3.14f + 90;

		window.render(missiles[i], missileAngle);
	}
}