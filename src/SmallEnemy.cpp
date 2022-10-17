#include "SmallEnemy.h"

SmallEnemy::SmallEnemy(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 0.75;

	previousTime = 0;
	maxTime = 0.2;

	counter = 0;

	shootCoolDown = false;
}

void SmallEnemy::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(1);

	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime && shootCoolDown)
	{
		previousTime = SDL_GetTicks() * 0.001;
		shootCoolDown = false;

		if (counter == 3)
		{
			maxTime = 2.5;
			counter = 0;
		}
		else if (counter < 3)
			maxTime = 0.2;
	}


	Shoot();

	SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

}

void SmallEnemy::Shoot()
{
	if (shootCoolDown)
		return;

	shootCoolDown = true;

	std::cout << "Working\n";
	
	counter++;

	Projectile temp = Projectile(Vector2f(110, 110), m_EnemyProjectile01, Vector2f(0.9, 0.9));
	temp.SetPos(Vector2f(GetPos().x, GetPos().y));

	projectiles.push_back(temp);
}

void SmallEnemy::GetTextures(SDL_Texture* p_EnemyProjectile01)
{
	m_EnemyProjectile01 = p_EnemyProjectile01;
}

void SmallEnemy::Render(RenderWindow window) {

	for (int i = 0; i < projectiles.size(); i++)
		window.render(projectiles[i], 0);
}