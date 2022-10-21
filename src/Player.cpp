#include "Player.h"

Player::Player(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 1.5;

	previousTime = 0;
	maxTime = 0.2;

	shootCoolDown = false;
}

void Player::Update()
{
	Entity::Update();

	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(-1);

	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime && shootCoolDown)
	{
		previousTime = SDL_GetTicks() * 0.001;
		shootCoolDown = false;
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].GetPos().y <= -10)
			projectiles[i].Destroy();
	}

	RemoveProjectiles();

}

void Player::HandleEvent(SDL_Event event)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_A])
		SetPos(Vector2f(GetPos().x - m_Speed, GetPos().y));

	else if (currentKeyStates[SDL_SCANCODE_D])
		SetPos(Vector2f(GetPos().x + m_Speed, GetPos().y));

	if (currentKeyStates[SDL_SCANCODE_W])
		SetPos(Vector2f(GetPos().x, GetPos().y - m_Speed));

	else if (currentKeyStates[SDL_SCANCODE_S])
		SetPos(Vector2f(GetPos().x, GetPos().y + m_Speed));

	if (currentKeyStates[SDL_SCANCODE_SPACE])
		Shoot();
}

void Player::Shoot()
{
	if (shootCoolDown)
		return;

	shootCoolDown = true;

	Projectile temp = Projectile(Vector2f(GetPos().x, GetPos().y), m_PlayerProjectile01, Vector2f(1, 1));

	projectiles.push_back(temp);
}

void Player::RemoveProjectiles()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].IsDestroy())
		{
			projectiles.erase(projectiles.begin() + i);
		}
	}
}

std::vector<Projectile>& Player::GetPlayerProjectiles()
{
	return projectiles;
}

void Player::GetTextures(SDL_Texture* p_PlayerProjectile01)
{
	m_PlayerProjectile01 = p_PlayerProjectile01;
}

void Player::Render(RenderWindow window) {

	for (int i = 0; i < projectiles.size(); i++)
	{
		if(!projectiles[i].IsDestroy())
			window.render(projectiles[i], 0);
	}
}