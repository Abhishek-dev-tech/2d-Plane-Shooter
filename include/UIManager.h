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

	void Render(RenderWindow& window);


private:

};
