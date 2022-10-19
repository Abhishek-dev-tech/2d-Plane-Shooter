#include "MediumEnemy.h"

MediumEnemy::MediumEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType)
	:Entity(p_pos, p_tex, p_scale)
{

	previousTime = 0;

	counter = 0;

	shootCoolDown = false;

	DefineShipType(p_shipType);

	m_CurrentFireRate = m_OriginalFireRate;
}

void MediumEnemy::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(1);

	if (SDL_GetTicks() * 0.001 - previousTime >= m_CurrentFireRate && shootCoolDown)
	{
		previousTime = SDL_GetTicks() * 0.001;
		shootCoolDown = false;
		if (counter == m_noOfBullets)
		{
			m_CurrentFireRate = m_ShootDelay;
			counter = 0;
		}
		else if (counter < m_noOfBullets)
			m_CurrentFireRate = m_OriginalFireRate;
	}

	Shoot(m_BulletOffset, m_bulletPair);

	SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

}

void MediumEnemy::Shoot(float p_bulletOffset, int p_bulletPair)
{
	if (shootCoolDown)
		return;

	shootCoolDown = true;	
	counter++;

	for (int i = 0; i < p_bulletPair; i++)
	{
		Projectile temp = Projectile(Vector2f(GetPos().x + m_BulletOffset * (i % 2 == 0 ? 1 : -1), GetPos().y), m_EnemyProjectile, Vector2f(0.9, 0.9));

		projectiles.push_back(temp);
	}
	
}

void MediumEnemy::DefineShipType(int type)
{
	switch (type)
	{
	case 1:
		m_shipType = DoubleShooter_Slower;
		m_BulletOffset = 12;
		m_bulletPair = 2;
		m_Speed = 0.5;
		m_OriginalFireRate = 0.1;
		m_noOfBullets = 5;
		m_ShootDelay = 3;
		break;

	case 2:
		m_shipType = DoubleShooter_Faster;
		m_BulletOffset = 0;
		m_bulletPair = 1;
		m_Speed = 0.7;
		m_OriginalFireRate = 0.15;
		m_noOfBullets = 3;
		m_ShootDelay = 2;
		break;

	case 3:
		m_shipType = Faster;
		m_BulletOffset = 12;
		m_bulletPair = 4;
		m_Speed = 0.85;
		m_OriginalFireRate = 0.1;
		m_noOfBullets = 2;
		m_ShootDelay = 2;
		break;

	default:
		break;
	}
}

void MediumEnemy::GetTextures(SDL_Texture* p_EnemyProjectile)
{
	m_EnemyProjectile = p_EnemyProjectile;
}

void MediumEnemy::Render(RenderWindow window) {

	for (int i = 0; i < projectiles.size(); i++)
		window.render(projectiles[i], 0);
}