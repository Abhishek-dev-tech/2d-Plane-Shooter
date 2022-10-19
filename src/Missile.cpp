#include "Missile.h"

Missile::Missile(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale)
	:Entity(p_pos, p_tex, p_scale)
{
	m_Speed = 0.005;

	counter = 1;
	maxTime = 5;

	followTarget = false;
}

void Missile::Update(Vector2f target)
{
	if (counter % 50 == 0)
	{
		followTarget = true;
	}

	if (!followTarget)
	{
		direction = Vector2f(360 - GetPos().x, 720 - GetPos().y);

		SetPos(Vector2f(GetPos().x + direction.x * m_Speed, GetPos().y + direction.y * m_Speed));
	}
	else
	{
		direction = Vector2f(target.x - GetPos().x, target.y - GetPos().y);

		SetPos(Vector2f(GetPos().x + direction.x * m_Speed, GetPos().y + direction.y * m_Speed));
	}
	
	counter++;
}