#pragma once
#include "SFML/Graphics.hpp";
#include "AssetManager.h";
#include <iostream>;
using namespace sf;

enum FoodType {DEFAULT, REVERSE, SPEED};

class Food
{
public:
	Food(const Vector2f& size, const Vector2f& position);
	bool ToggleReverseModifier(); // for use with GUI
	bool ToggleSpeedModifier(); // for use with GUI
	bool SpeedModifierEnabled();
	bool ReversemodifierEnabled();
	void SetFoodTexture(const string& filename); // apply textures to food
	void SetRandomFoodType();
	void SetFoodPosition(const Vector2f& position);
	Vector2f GetFoodPosition();
	FoodType GetCurrentFoodType(); // returns the current food type
	void DrawFood(RenderWindow& r_renderWindow); // draws food to window provided
private:
	bool m_reverseModifierEnable = false;
	bool m_speedModifierEnable = false;
	FoodType m_currentFoodType = DEFAULT;
	RectangleShape m_food;
};

