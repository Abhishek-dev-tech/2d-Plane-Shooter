#include "MediumEnemy.h"

MediumEnemy::MediumEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 0.6;

	previousTime = 0;
	maxTime = 0.15;

	counter = 0;
	bulletOffset = 12;

	shootCoolDown = false;
}

void MediumEnemy::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(1);

	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime && shootCoolDown)
	{
		previousTime = SDL_GetTicks() * 0.001;
		shootCoolDown = false;

		if (counter == 4)
		{
			maxTime = 2.5;
			counter = 0;
		}
		else if (counter < 4)
			maxTime = 0.15;
	}

	Shoot();

	SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

}

void MediumEnemy::Shoot()
{
	if (shootCoolDown)
		return;

	shootCoolDown = true;
	counter++;

	Projectile temp1 = Projectile(Vector2f(GetPos().x + bulletOffset, GetPos().y), m_EnemyProjectile01, Vector2f(0.9, 0.9));

	Projectile temp2 = Projectile(Vector2f(GetPos().x - bulletOffset, GetPos().y), m_EnemyProjectile01, Vector2f(0.9, 0.9));

	projectiles.push_back(temp1);
	projectiles.push_back(temp2);
}

void MediumEnemy::GetTextures(SDL_Texture* p_EnemyProjectile01)
{
	m_EnemyProjectile01 = p_EnemyProjectile01;
}

void MediumEnemy::Render(RenderWindow window) {

	for (int i = 0; i < projectiles.size(); i++)
		window.render(projectiles[i], 0);
}