#include "Player.h"
#include "Texture.h"
#include "ObjectSpawner.h"
#include "UIManager.h"

Player::Player(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 1.5;

	previousTime = 0;
	maxTime = 0.2;

	shootCoolDown = false;
	missileCoolDown = false;
	flareCoolDown = true;

	once = true;

	m_MissileMaxTime = 7;
	m_FlaresMaxTime = 0.1;

	hitPoints = 50;

	originalScale = Vector2f(2.25, 2.25);

}

void Player::Update()
{
	if (!IsDestroy())
	{
		Entity::Update();

		for (int i = 0; i < projectiles.size(); i++)
			projectiles[i].Update(-1);

		for (int i = 0; i < flares.size(); i++)
			flares[i].Update();

		if (!missile.IsDestroy() && !once)
			missile.Update(*m_Target);


		if (SDL_GetTicks() * 0.001 - previousTime >= maxTime && shootCoolDown)
		{
			previousTime = SDL_GetTicks() * 0.001;
			shootCoolDown = false;
		}

		if (!m_MissileTimer.IsStarted())
			m_MissileTimer.Start();

		if (m_MissileTimer.GetTicks() * 0.001 >= m_MissileMaxTime)
		{
			missileCoolDown = false;
			m_MissileTimer.Stop();
		}

		if (missile.IsDestroy())
			once = true;

		SetScale(Vector2f(Mathf::Lerp(GetScale().x, originalScale.x, 0.1), Mathf::Lerp(GetScale().y, originalScale.y, 0.1)));


		ShootFlares();

		RemoveUnwantedStuff();
	}
}

void Player::HandleEvent(SDL_Event event)
{
	if (!IsDestroy())
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

		if (currentKeyStates[SDL_SCANCODE_E])
			flareCoolDown = false;

		if (currentKeyStates[SDL_SCANCODE_SPACE])
			Shoot();

		if (event.type == SDL_MOUSEBUTTONDOWN)
			ShootMissile();
	}
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

void Player::ShootFlares()
{
	if (!m_FlareTimer.IsStarted())
		m_FlareTimer.Start();

	if (!flareCoolDown && m_FlareTimer.GetTicks() * 0.001 >= m_FlaresMaxTime)
	{
		flareCounter++;
		
		Flare temp = Flare(Vector2f(GetPos().x, GetPos().y), Texture::GetInstance().flare, Vector2f(1.75, 1.75), flareCounter % 2 == 0 ? 1 : -1, flareCounter % 2 == 0 ? 100 : -100);
		ObjectSpawner::GetInstance().SpawnSmokEffect(Vector2f(GetPos().x, GetPos().y), Vector2f(5, 5));

		flares.push_back(temp);
		m_FlareTimer.Stop();

		if (flareCounter >= 8)
			flareCoolDown = true;
	}
}

void Player::Damage(int damage)
{
	SetScale(Vector2f(originalScale.x + 0.3, originalScale.y + 0.3));

	hitPoints -= damage;
	UIManager::GetInstance().UpdateHealthBar();


	if (hitPoints <= 0)
	{
		Destroy();
		ObjectSpawner::GetInstance().SpawnBlastEffect(GetPos(), Vector2f(8, 8));
		ObjectSpawner::GetInstance().SpawnSmokEffect(GetPos(), Vector2f(8, 8));
	}
}

void Player::RemoveUnwantedStuff()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].GetPos().y <= -10)
			projectiles[i].Destroy();

		if (projectiles[i].IsDestroy())
			projectiles.erase(projectiles.begin() + i);
		
	}

	for (int i = 0; i < flares.size(); i++)
	{
		if (flares[i].GetPos().y >= 730 || flares[i].GetPos().x >= 730 || flares[i].GetPos().x <= -10)
			flares[i].Destroy();

		if (flares[i].IsDestroy())
			flares.erase(flares.begin() + i);
		
	}
}

std::vector<Projectile>& Player::GetPlayerProjectiles()
{
	return projectiles;
}

Missile& Player::GetMissile()
{
	return missile;
}

std::vector<Flare>& Player::GetFlares()
{
	return flares;
}

void Player::SetPlayerMissileTarget(Vector2f* p_Target)
{
	m_Target = p_Target;
}

int Player::GetHitPoints()
{
	return hitPoints;
}

void Player::Render(RenderWindow& window) {

	for (int i = 0; i < projectiles.size(); i++)
		if(!projectiles[i].IsDestroy())
			window.render(projectiles[i], 0, false);

	if (!missile.IsDestroy() && !once)
	{
		missileAngle = atan2(m_Target->y - missile.GetPos().y, m_Target->x - missile.GetPos().x) * 180.0f / 3.14f + 90;
		
		window.render(missile, missileAngle, false);
	}

	for (int i = 0; i < flares.size(); i++)
		if (!flares[i].IsDestroy())
			window.render(flares[i], flares[i].m_Angle, false);
}