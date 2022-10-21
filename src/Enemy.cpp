#include "Enemy.h"
#include "Mathf.h"

Enemy::Enemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	previousTime = 0;

	counter = 0;

	shootCoolDown = false;

	originalScale = p_scale;

	m_CurrentFireRate = m_OriginalFireRate;
}

void Enemy::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(1);

	RemoveProjectiles();

	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].GetPos().y >= 730)
			projectiles[i].Destroy();
	}

	if (IsDestroy())
		return;

	Entity::Update();


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

	SetScale(Vector2f(Mathf::Lerp(GetScale().x, originalScale.x, 0.1), Mathf::Lerp(GetScale().y, originalScale.y, 0.1)));

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

void Enemy::RemoveProjectiles()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].IsDestroy())
		{
			projectiles.erase(projectiles.begin() + i);
		}
	}
}

void Enemy::Damage(int value)
{
	SetScale(Vector2f(originalScale.x + 0.3, originalScale.y + 0.3));

	hitPoints -= value;

	if (hitPoints <= 0)
		Destroy();
}

void Enemy::GetTextures(SDL_Texture* p_EnemyProjectile)
{
	m_EnemyProjectile = p_EnemyProjectile;
}

std::vector<Projectile>& Enemy::GetProjectiles()
{
	return projectiles;
}


void Enemy::Render(RenderWindow window) {

	for (int i = 0; i < projectiles.size(); i++)
		if(!projectiles[i].IsDestroy())
			window.render(projectiles[i], 0);
}