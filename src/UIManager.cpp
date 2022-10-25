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

}

void UIManager::PositionAndScalingUI()
{
	Texture::GetInstance().m_HealthBar.SetPos(Vector2f(80, 700));
	Texture::GetInstance().m_HealthBar.SetScale(Vector2f(4, 0.5));

}

void UIManager::UpdateHealthBar()
{
	int hitpoints = Texture::GetInstance().m_PlayerShip.GetHitPoints();

	float scale = Texture::GetInstance().m_HealthBar.GetScale().x - ((((float)hitpoints / 50.0) * 4.0));


	Texture::GetInstance().m_HealthBar.SetScale(Vector2f(Texture::GetInstance().m_HealthBar.GetScale().x - scale, 0.5));
	Texture::GetInstance().m_HealthBar.SetPos(Vector2f(Texture::GetInstance().m_HealthBar.GetPos().x - scale - 1.222, 700));
}

void UIManager::Render(RenderWindow& window)
{
	window.render(Texture::GetInstance().m_HealthBar, 0, false);
}