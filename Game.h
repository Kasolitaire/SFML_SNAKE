#pragma once
#include "SFML/Window.hpp";
#include "SFML/Graphics.hpp";
#include "Global.h";
#include <iostream>; 
#include "GUI.h";
using std::vector;
using namespace sf;

class Game
{
public:
	Game(RenderWindow& renderWindow);
	void StartGame();
private:
	static bool OutOfBoundsLoseState(const Vector2f headSegmentPosition);
	static bool CollisionLoseState(const vector<RectangleShape*>& segments, const Vector2f headSegmentPosition);
	static bool FoodCollision(Vector2f foodPosition, vector<Vector2f> segmentPositions);
	Vector2f GetLegalFoodPosition(vector<Vector2f> segmentPositions);
	void Clear();
	void Display();
	void StandardGameLoop();
	void HandleInput();
	Time UpdateClock();
	void Draw(Snake& r_snake); 
	RenderWindow& m_renderWindow;
	RectangleShape m_food;
	Vector2f** m_Grid;
	GUI m_GUI;
	Clock m_clock;
	Time m_totalTimeElapsed;
	Snake m_snake;
	int m_GridColumns = 0;
	int m_GridRows = 0;
};

