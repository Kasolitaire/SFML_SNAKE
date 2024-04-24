#pragma once
#include "SFML/Graphics.hpp";
#include "AssetManager.h";
using namespace sf;

enum FoodType {DEFAULT, REVERSE, SPEED};

class Food
{
public:
	bool ToggleReverseModifier();
	bool ToggleSpeedModifier();
	void SetFoodTexture();
private:
	bool m_reverseModifierEnable = false;
	bool m_speedModifierEnable = false;
	FoodType m_currentFoodType = DEFAULT;
	RectangleShape m_food;
};

