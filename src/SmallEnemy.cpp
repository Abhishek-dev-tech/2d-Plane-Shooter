#include "SmallEnemy.h"

SmallEnemy::SmallEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, int p_shipType)
	:Entity(p_pos, p_tex, p_scale)
{
	previousTime = 0;

	counter = 0;

	shootCoolDown = false;

	DefineShipType(p_shipType);

	m_CurrentFireRate = m_OriginalFireRate;
}

void SmallEnemy::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(1);

	if (SDL_GetTicks() * 0.001 - previousTime >= m_CurrentFireRate && shootCoolDown)
	{
		previousTime = SDL_GetTicks() * 0.001;
		shootCoolDown = false;

		if (counter == m_noOfBullets)
		{
			m_CurrentFireRate = m_shootDelay;
			counter = 0;
		}
		else if (counter < 3)
			m_CurrentFireRate = m_OriginalFireRate;
	}


	Shoot(m_bulletOffset, m_bulletPair);

	SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

}

void SmallEnemy::DefineShipType(int type)
{
	switch (type)
	{
		case 1:
			m_shipType = SingleShooter;
			m_bulletOffset = 0;
			m_bulletPair = 1;
			m_Speed = 0.75;
			m_OriginalFireRate = 0.2;
			m_noOfBullets = 3;
			m_shootDelay = 2;
			break;

		case 2:
			m_shipType = DoubleShooter;
			m_bulletOffset = 10;
			m_bulletPair = 2;
			m_Speed = 0.6;
			m_OriginalFireRate = 0.15;
			m_noOfBullets = 2;
			m_shootDelay = 1.5;
			break;

		case 3:
			m_shipType = Faster;
			m_bulletOffset = 10;
			m_bulletPair = 2;
			m_Speed = 1;
			m_OriginalFireRate = 0.15;
			m_noOfBullets = 1;
			m_shootDelay = 2.5;
			break;

	default:
		break;
	}
}

void SmallEnemy::Shoot(float p_bulletOffset, int p_bulletPair)
{
	if (shootCoolDown)
		return;

	shootCoolDown = true;	
	counter++;

	for (int i = 0; i < p_bulletPair; i++)
	{
		Projectile temp = Projectile(Vector2f(GetPos().x + m_bulletOffset * (i % 2 == 0 ? 1 : -1), GetPos().y), m_EnemyProjectile, Vector2f(0.9, 0.9));

		projectiles.push_back(temp);
	}
	
}

void SmallEnemy::GetTextures(SDL_Texture* p_EnemyProjectile)
{
	m_EnemyProjectile = p_EnemyProjectile;
}

void SmallEnemy::Render(RenderWindow window) {

	for (int i = 0; i < projectiles.size(); i++)
		window.render(projectiles[i], 0);
}