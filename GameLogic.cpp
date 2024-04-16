#include <random>;
#include <iostream>;
#include "SFML/Audio.hpp";
#include "AssetManager.h"
#include "GameLogic.h"
using namespace std;
bool GameLogic::OutOfBoundsLoseState(Vector2f headSegmentPosition) 
{
	if (headSegmentPosition.x >= WINDOW_RESOLUTION.x || headSegmentPosition.x < 0 || headSegmentPosition.y >= WINDOW_RESOLUTION.y || headSegmentPosition.y < 0)
	{
		return true;
	}
	return false;
}

bool GameLogic::CollisionLoseState(const vector<RectangleShape*>& segments, const Vector2f headSegmentPosition)
{
	for (int i = 0; i < segments.size(); i++) 
	{
		if (headSegmentPosition.x == segments[i]->getPosition().x && headSegmentPosition.y == segments[i]->getPosition().y)
			return true;
	}
	return false;
}

Vector2f GameLogic::GetLegalFoodPosition(vector<Vector2f> segmentPositions)
{
	const int gridColumns = m_GridColumns;
	const int gridRows = m_GridRows;
	vector<Vector2f> legalPositions;
	for (int i = 0; i < m_GridColumns; i++)
	{
		for (int j = 0; j < m_GridRows; j++)
		{
			bool legal = true;
			for (int k = 0; k < segmentPositions.size(); k++)
			{
				if (segmentPositions[k].x == m_Grid[i][j].x && segmentPositions[k].y == m_Grid[i][j].y)
					legal  = false;
			}
			if(legal)
				legalPositions.push_back(m_Grid[i][j]);
		}
	}

	random_device rd;
 	uniform_int_distribution<int> dist(0, legalPositions.size() - 1);
	
	return legalPositions[dist(rd)];
}

bool GameLogic::FoodCollision(Vector2f foodPosition, vector<Vector2f> segmentPositions)
{
	vector<Vector2f>::iterator iter;
	for (iter = segmentPositions.begin(); iter != segmentPositions.end(); ++iter) 
	{
		if (iter -> x == foodPosition.x && iter -> y == foodPosition.y)
			return true;
	}
	return false;
}

GameLogic::GameLogic(RenderWindow& renderWindow) : m_renderWindow(renderWindow), m_GUI(GUI(renderWindow)) // not sure why angry since it should call default constructor
{
	int rows = 0;
	int columns = 0;

	for (int x = 0; x < WINDOW_RESOLUTION.x; x += SEGMENT_SIZE.x)
	{
		columns++;
	}
	for (int y = 0; y < WINDOW_RESOLUTION.y; y += SEGMENT_SIZE.y)
	{
		rows++;
	}
	Vector2f** a2d = new Vector2f * [columns];
	// variables for columns and rows
	int incrementX = 0;
	int incrementY = 0;
	for (int i = 0; i < columns; i++)
	{
		a2d[i] = new Vector2f[rows];
		for (int j = 0; j < rows; j++)
		{
			a2d[i][j] = Vector2f(incrementX, incrementY);

			//std::cout << a2d[i][j].x << " " << a2d[i][j].y << std::endl;
			incrementY += SEGMENT_SIZE.y;
		}
		incrementX += SEGMENT_SIZE.x;
		incrementY = 0;
	}
	m_Grid = a2d;
	m_GridColumns = columns;
	m_GridRows = rows;
}

bool GameLogic::StartGame()
{
	// inside the main loop, between window.clear() and window.display()
	
	while (m_renderWindow.isOpen())
	{
		if (m_GUI.m_GUIOpen) 
		{
			m_renderWindow.clear();
			m_GUI.DrawText();
			m_renderWindow.display();
			while (m_renderWindow.pollEvent(m_event))
			{
				m_renderWindow.clear();
				m_GUI.DrawText();
				m_renderWindow.display();
				if (m_GUI.CheckForPlay()) 
				{
					cout << "play" << endl;
					m_GUI.m_GUIOpen = false;
				} 
				else if (m_GUI.CheckForExit()) 
				{
					m_renderWindow.close();
				}
			}
		}
		else 
		{
			StandardGameLoop();
			m_GUI.m_GUIOpen = true;
		}
	}
	return false;
}

bool GameLogic::StandardGameLoop()
{
	
	Sound sound(AssetManager::GetSoundBuffer("assets\\question.wav"));
	sound.setVolume(100);
	
	Snake snake(SEGMENT_SIZE, HEAD_COLOR, WINDOW_RESOLUTION);
	RectangleShape food;
	food.setSize(Vector2f(SEGMENT_SIZE.x, SEGMENT_SIZE.y));
	food.setFillColor(Color::Red);
	Vector2f legalFoodPosition = GetLegalFoodPosition(snake.GetAllSegmentPositions());
	food.setPosition(legalFoodPosition);
	UniqueTimeTracker speedUpTracker;

	while (m_renderWindow.isOpen()) 
	{
		while (m_renderWindow.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_renderWindow.close();
			if (m_event.type == Event::KeyPressed)
			{
				switch (m_event.key.code)
				{
				case Keyboard::Key::W:
					snake.SetDirection(UP);
					break;
				case Keyboard::Key::S:
					snake.SetDirection(DOWN);
					break;
				case Keyboard::Key::A:
					snake.SetDirection(RIGHT);
					break;
				case Keyboard::Key::D:
					snake.SetDirection(LEFT);
					break;
				case Keyboard::Key::Space:
					snake.AddSegment();
				default:
					break;
				}
			}
		}

		m_renderWindow.clear();
		m_GUI.DrawScore();
		m_renderWindow.draw(food);
		snake.DrawHeadSegment(m_renderWindow);
		snake.DrawSegments(m_renderWindow);
		/*if (speedUpTracker.HasTimeElapsedOnce(2))
			snake.AdjustRefreshPeriod(2);*/
		if (snake.MoveAlongSnake())
		{
			if (GameLogic::OutOfBoundsLoseState(snake.GetLocation())) // checks if head segement is no longer in viewscope
			{
				cout << "out of bounds" << " " << snake.GetAllSegmentPositions()[0].x << endl;
				break;
			}
			if (GameLogic::CollisionLoseState(snake.GetSegmentsAsReference(), snake.GetLocation()))
			{
				cout << "collision detected" << endl;
				//lose text
				break;
			}
			if (GameLogic::FoodCollision(food.getPosition(), snake.GetAllSegmentPositions()))
			{
				Vector2f legalFoodPosition = GetLegalFoodPosition(snake.GetAllSegmentPositions());
				food.setPosition(legalFoodPosition);
				snake.AddSegment();
				m_GUI.IncrementScore();
				//snake.MoveHeadToBack();
				/*snake.AdjustRefreshPeriod(0.5);
				speedUpTracker.StartClock();*/

				
				sound.play();
			}
		}
		
		m_renderWindow.display();
	}
	return false;
}

