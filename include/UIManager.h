#pragma once
#include "Texture.h"

class UIManager
{
public:
	UIManager();

	static UIManager& GetInstance();

	void Update();

	void PositionAndScalingUI();
	void UpdateHealthBar();

	void SetRenderer(SDL_Renderer* renderer);

	void Render(RenderWindow& window);


private:

	std::string m_MissileText;
	std::string m_FlareText;

	SDL_Color m_White = { 255, 255, 255 };
	SDL_Color m_Black = { 0, 0, 0 };

	SDL_Renderer* m_Renderer;


};
