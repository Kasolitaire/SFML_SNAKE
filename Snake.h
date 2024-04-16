#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>;
#include "Global.h";
using namespace std;
using namespace sf;

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake
{
public:
	// need to create copy constructor
	Snake(const Vector2f segmentSize, const Color color, Vector2u windowResolution);
	~Snake();
	bool DrawHeadSegment(RenderWindow& renderWindow); // returns true when drawn
	bool SetDirection(Direction desiredDirection);
	void AddSegment();
	bool MoveAlongSnake();
	void DrawSegments(RenderWindow& renderWindow);
	void AdjustRefreshPeriod(const float refreshMultiplier);
	void ReverseSegments();
	Vector2f GetLocation(); // could be made one function instead of two
	vector<RectangleShape*>& GetSegmentsAsReference();
	vector<Vector2f> GetAllSegmentPositions();
	void MoveHeadToBack();
private: 
	RectangleShape* CreateSegment();
	bool MoveHeadSegmentSetPeriod();
	void MoveAlongSegments();
	RectangleShape m_SnakeHeadRect;
	vector<RectangleShape*> m_SnakeSegmentsRect;
	Vector2f m_previousPositionLastSegment;
	Clock clock;
	Direction m_currentDirection = LEFT;
	Direction m_desiredDirection = LEFT;
	Vector2f m_PreviousHeadPosition;
	int m_IncrementAmmount;
	float m_TimeToMoveSeconds = REFRESH_PERIOD;
};