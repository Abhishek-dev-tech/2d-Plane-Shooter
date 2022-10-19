#include "BigEnemy.h"

BigEnemy::BigEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType)
	:Entity(p_pos, p_tex, p_scale)
{
	previousTime = 0;
	missileAngle = 180;

	counter = 0;

	shootCoolDown = false;
	missileCoolDown = false;

	DefineShipType(p_shipType);

	m_CurrentFireRate = m_OriginalFireRate;
}

void BigEnemy::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(1);

	for (int i = 0; i < missiles.size(); i++)
		missiles[i].Update(m_Player->GetPos());

	if (SDL_GetTicks() * 0.001 - previousTime >= m_CurrentFireRate && shootCoolDown)
	{
		previousTime = SDL_GetTicks() * 0.001;
		shootCoolDown = false;

		if (counter == m_noOfBullets)
		{
			m_CurrentFireRate = m_ShootDelay;
			ShootMissiles();
			counter = 0;
		}
		else if (counter < m_noOfBullets)
			m_CurrentFireRate = m_OriginalFireRate;
	}



	ShootBullets(m_BulletOffset, m_bulletPair);

	SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

}

void BigEnemy::ShootBullets(float p_bulletOffset, int p_bulletPair)
{
	if (shootCoolDown)
		return;

	shootCoolDown = true;
	counter++;

	for (int i = 0; i < p_bulletPair; i++)
	{
		Projectile temp1 = Projectile(Vector2f(GetPos().x + m_BulletOffset * (i % 2 == 0 ? 1 : -1), GetPos().y), m_EnemyProjectile, Vector2f(0.9, 0.9));
		Projectile temp2 = Projectile(Vector2f(temp1.GetPos().x + 8 * (i % 2 == 0 ? 1 : -1), GetPos().y), m_EnemyProjectile, Vector2f(0.9, 0.9));

		projectiles.push_back(temp1);
		projectiles.push_back(temp2);
	}


}

void BigEnemy::ShootMissiles()
{
	if (missileCoolDown)
		return;

	missileCoolDown = true;

	Missile temp = Missile(Vector2f(GetPos().x, GetPos().y), m_Missile, Vector2f(2, 2));

	missiles.push_back(temp);
}

void BigEnemy::DefineShipType(int type)
{
	switch (type)
	{
	case 1:
		m_shipType = QuardShooter_SingleMissile_Slower;
		m_BulletOffset = 16;
		m_bulletPair = 2;
		m_Speed = 0.5;
		m_OriginalFireRate = 0.1;
		m_noOfBullets = 7;
		m_ShootDelay = 3;
		break;

	case 2:
		m_shipType = QuardShooter_DoubleMissile_Faster;
		m_BulletOffset = 16;
		m_bulletPair = 2;
		m_Speed = 0.7;
		m_OriginalFireRate = 0.15;
		m_noOfBullets = 3;
		m_ShootDelay = 2;
		break;

	case 3:
		m_shipType = Faster;
		m_BulletOffset = 16;
		m_bulletPair = 2;
		m_Speed = 0.85;
		m_OriginalFireRate = 0.2;
		m_noOfBullets = 2;
		m_ShootDelay = 1;
		break;

	default:
		break;
	}
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