#include "UIManager.h"

#include <string>

UIManager::UIManager()
{
	PositionAndScalingUI();

	m_Score = 0;
	m_ScoreText = "Score: 0";

	m_ScoreMultiplerMaxTime = 0;
	m_ScoreMultipler = 1;
}

UIManager& UIManager::GetInstance()
{
	static UIManager* instance = new UIManager;

	return *instance;
}

void UIManager::Update()
{
	if (!Texture::GetInstance().m_PlayerShip.missileCoolDown)
		m_MissileText = "x 1";
	else
		m_MissileText = "x 0";
	
	if (!Texture::GetInstance().m_PlayerShip.flareCoolDown)
		m_FlareText = "x 1";
	else
		m_FlareText = "x 0";

	UpdateScoreMultiplyerBar();

}

void UIManager::PositionAndScalingUI()
{
	Texture::GetInstance().m_HealthBar.SetPos(Vector2f(90, 700));
	Texture::GetInstance().m_HealthBar.SetScale(Vector2f(4, 0.5));
	
	Texture::GetInstance().m_ScoreMultiplierBar.SetPos(Vector2f(630, 700));
	Texture::GetInstance().m_ScoreMultiplierBar.SetScale(Vector2f(4, 0.5));
	
	Texture::GetInstance().m_MissileIcon.SetPos(Vector2f(40, 675));

	Texture::GetInstance().m_FlareIcon.SetPos(Vector2f(40, 640));

}

void UIManager::UpdateHealthBar()
{
	int hitpoints = Texture::GetInstance().m_PlayerShip.GetHitPoints();

	float scale = Texture::GetInstance().m_HealthBar.GetScale().x - ((((float)hitpoints / 50.0) * 4.0));


	Texture::GetInstance().m_HealthBar.SetScale(Vector2f(Texture::GetInstance().m_HealthBar.GetScale().x - scale, 0.5));
	Texture::GetInstance().m_HealthBar.SetPos(Vector2f(Texture::GetInstance().m_HealthBar.GetPos().x - scale - 1.222, 700));
}

void UIManager::UpdateScoreMultiplyerBar()
{
	if (!m_ScoreMultiplerTimer.IsStarted() && m_Kills >= 1)
		m_ScoreMultiplerTimer.Start();

	m_ScoreMultiplerMaxTime = m_Kills;

	if (m_ScoreMultiplerTimer.GetTicks() * 0.001 < m_ScoreMultiplerMaxTime && m_Kills >= 1)
	{
		float scale = (m_ScoreMultiplerTimer.GetTicks() * 0.001 / m_ScoreMultiplerMaxTime);

		Texture::GetInstance().m_ScoreMultiplierBar.SetScale(Vector2f(Texture::GetInstance().m_ScoreMultiplierBar.GetScale().x - scale, 0.5));
		//Texture::GetInstance().m_ScoreMultiplierBar.SetPos(Vector2f(Texture::GetInstance().m_ScoreMultiplierBar.GetPos().x - scale - 1.222, 700));

		if (Texture::GetInstance().m_ScoreMultiplierBar.GetScale().x >= 4)
			Texture::GetInstance().m_ScoreMultiplierBar.SetScale(Vector2f(4, 0.5));

		if (Texture::GetInstance().m_ScoreMultiplierBar.GetScale().x <= 0)
			m_ScoreMultipler = 0;
		
	}
	else
		m_ScoreMultiplerTimer.Stop();

	


}

void UIManager::UpdateScore(int p_Score)
{
	m_Score += p_Score * m_ScoreMultipler;
	m_ScoreText = "Score: " + std::to_string(m_Score);
}

void UIManager::SetRenderer(SDL_Renderer* renderer)
{
	m_Renderer = renderer;
}

void UIManager::SetKills(int p_Kills)
{
	m_Kills += p_Kills;
}

void UIManager::Render(RenderWindow& window)
{
	window.Render(Texture::GetInstance().m_HealthBar, 0, false);
	window.Render(Texture::GetInstance().m_ScoreMultiplierBar, 0, false);

	window.Render(Texture::GetInstance().m_MissileIcon, 0, false);
	window.Render(Texture::GetInstance().m_FlareIcon, 0, false);

	//Texts
	window.RenderText(Vector2f(67, 675), m_MissileText, Texture::GetInstance().font16, m_White);
	window.RenderText(Vector2f(67, 640), m_FlareText, Texture::GetInstance().font16, m_White);
	window.RenderText(Vector2f(630, 660), m_ScoreText, Texture::GetInstance().font28, m_White);
}