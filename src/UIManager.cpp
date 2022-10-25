#include "UIManager.h"

UIManager::UIManager()
{
	PositionAndScalingUI();
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
}

void UIManager::PositionAndScalingUI()
{
	Texture::GetInstance().m_HealthBar.SetPos(Vector2f(90, 700));
	Texture::GetInstance().m_HealthBar.SetScale(Vector2f(4, 0.5));
	
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

void UIManager::SetRenderer(SDL_Renderer* renderer)
{
	m_Renderer = renderer;
}

void UIManager::Render(RenderWindow& window)
{
	window.Render(Texture::GetInstance().m_HealthBar, 0, false);

	window.Render(Texture::GetInstance().m_MissileIcon, 0, false);
	window.Render(Texture::GetInstance().m_FlareIcon, 0, false);

	window.RenderText(Vector2f(67, 675), m_MissileText, Texture::GetInstance().font16, m_White);

	window.RenderText(Vector2f(67, 640), m_FlareText, Texture::GetInstance().font16, m_White);
}