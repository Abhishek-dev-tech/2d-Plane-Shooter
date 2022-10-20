#include "Enemy.h"

Enemy::Enemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	previousTime = 0;

	counter = 0;

	shootCoolDown = false;

	m_CurrentFireRate = m_OriginalFireRate;
}

void Enemy::Update()
{
	Entity::Update();

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

void Enemy::Shoot(float p_bulletOffset, int p_bulletPair)
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

void Enemy::GetTextures(SDL_Texture* p_EnemyProjectile)
{
	m_EnemyProjectile = p_EnemyProjectile;
}

void Enemy::Render(RenderWindow window) {

	for (int i = 0; i < projectiles.size(); i++)
		window.render(projectiles[i], 0);
}