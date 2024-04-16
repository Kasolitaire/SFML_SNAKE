#pragma once
#include "SFML/Window.hpp";
#include "SFML/Graphics.hpp";
#include "Global.h";
#include <iostream>; 
#include "GUI.h";
#include "UniqueTimeTracker.h";
using std::vector;
using namespace sf;

class GameLogic
{
public:
	GameLogic(RenderWindow& renderWindow);
	static bool OutOfBoundsLoseState(const Vector2f headSegmentPosition);
	static bool CollisionLoseState(const vector<RectangleShape*>& segments, const Vector2f headSegmentPosition);
	static bool FoodCollision(Vector2f foodPosition, vector<Vector2f> segmentPositions);
	Vector2f GetLegalFoodPosition(vector<Vector2f> segmentPositions);
	bool StartGame();
	bool StandardGameLoop();
private:
	RenderWindow& m_renderWindow;
	Vector2f** m_Grid;
	GUI m_GUI;
	Event m_event;
	Clock m_clock;
	int m_GridColumns = 0;
	int m_GridRows = 0;
};

