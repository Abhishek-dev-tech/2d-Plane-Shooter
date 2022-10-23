#include "Player.h"
#include "Texture.h"


Player::Player(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 1.5;

	previousTime = 0;
	maxTime = 0.2;

	shootCoolDown = false;
	missileCoolDown = false;
}

void Player::Update()
{
	Entity::Update();

	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update(-1);

	missile.Update(*m_Target);

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

	if (event.type == SDL_MOUSEBUTTONDOWN)
		ShootMissile();
}

void Player::Shoot()
{
	if (!shootCoolDown)
	{
		shootCoolDown = true;

		Projectile temp = Projectile(Vector2f(GetPos().x, GetPos().y), Texture::GetInstance().projectile01, Vector2f(1, 1));

		projectiles.push_back(temp);
	}
}

void Player::ShootMissile()
{
	if (!missileCoolDown && Texture::GetInstance().isCursorCollideWithEnemy)
	{
		missileCoolDown = true;

		Missile temp = Missile(Vector2f(GetPos().x, GetPos().y), Texture::GetInstance().missile, Vector2f(2, 2));

		missile = temp;
	}
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

void Player::SetPlayerMissileTarget(Vector2f* p_Target)
{
	m_Target = p_Target;
}

void Player::Render(RenderWindow window) {

	for (int i = 0; i < projectiles.size(); i++)
		if(!projectiles[i].IsDestroy())
			window.render(projectiles[i], 0);

	if (!missile.IsDestroy())
	{
		missileAngle = (float)std::atan2(m_Target->y - missile.GetPos().y, m_Target->x - missile.GetPos().x) * 180.0f / 3.14f + 90;
		window.render(missile, missileAngle);
	}
		
		
			
	
	
}