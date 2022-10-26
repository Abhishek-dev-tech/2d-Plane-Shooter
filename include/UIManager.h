#pragma once
#include "Texture.h"
#include "Timer.h"

class UIManager
{
public:
	UIManager();

	static UIManager& GetInstance();

	void Update();

	void PositionAndScalingUI();
	void UpdateHealthBar();
	void UpdateScore(int p_Score);

	void SetRenderer(SDL_Renderer* renderer);
	void SetKills(int p_Kills);
	void ResetHealthBar();

	void Render(RenderWindow& window);


private:

	std::string m_MissileText;
	std::string m_FlareText;

	std::string m_ScoreText;

	int m_Score;
	int m_Kills;

	Vector2f m_HealthBarOriginalPos;
	Vector2f m_HealthBarOriginalScale;

	SDL_Color m_White = { 255, 255, 255 };
	SDL_Color m_Black = { 0, 0, 0 };

	SDL_Renderer* m_Renderer;
};
