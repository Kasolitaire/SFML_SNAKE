#include <random>;
#include <iostream>;
#include "SFML/Audio.hpp";
#include "AssetManager.h";
#include "Game.h";

using namespace std;
bool Game::OutOfBoundsLoseState(Vector2f headSegmentPosition) 
{
	if (headSegmentPosition.x >= WINDOW_RESOLUTION.x || headSegmentPosition.x < 0 || headSegmentPosition.y >= WINDOW_RESOLUTION.y || headSegmentPosition.y < 0)
	{
		return true;
	}
	return false;
}

bool Game::CollisionLoseState(const vector<RectangleShape*>& segments, const Vector2f headSegmentPosition)
{
	for (int i = 0; i < segments.size(); i++) 
	{
		if (headSegmentPosition.x == segments[i]->getPosition().x && headSegmentPosition.y == segments[i]->getPosition().y)
			return true;
	}
	return false;
}

Vector2f Game::GetLegalFoodPosition(vector<Vector2f> segmentPositions)
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

void Game::Clear()
{
	m_renderWindow.clear(Color::Red);
}

void Game::Display()
{
	m_renderWindow.display();
}

bool Game::FoodCollision(Vector2f foodPosition, vector<Vector2f> segmentPositions)
{
	vector<Vector2f>::iterator iter;
	for (iter = segmentPositions.begin(); iter != segmentPositions.end(); ++iter) 
	{
		if (iter -> x == foodPosition.x && iter -> y == foodPosition.y)
			return true;
	}
	return false;
}

Game::Game(RenderWindow& renderWindow) : m_renderWindow(renderWindow), m_GUI(GUI(renderWindow)) // not sure why angry since it should call default constructor
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

void Game::StartGame()
{
	// inside the main loop, between window.clear() and window.display()
	
	while (m_renderWindow.isOpen())
	{
		Event event;
		if (m_GUI.m_GUIOpen) 
		{
			if (m_GUI.CheckForPlay())
			{
				cout << "play" << endl;
				m_GUI.m_GUIOpen = false;
			}
			else if (m_GUI.CheckForExit())
			{
				m_renderWindow.close();
			}
			
			m_renderWindow.clear();
			m_GUI.DrawText();
			m_renderWindow.display();
		}
		else 
		{
			StandardGameLoop();
			m_GUI.m_GUIOpen = true;
		}
	}
}

Time Game::UpdateClock()
{
	Time deltaTime = m_clock.getElapsedTime();
	m_totalTimeElapsed += deltaTime;
	m_clock.restart();
	return deltaTime;
}

void Game::Draw(Snake& r_snake)
{
	m_renderWindow.draw(m_food);
	r_snake.DrawHeadSegment(m_renderWindow);
	r_snake.DrawSegments(m_renderWindow);
	m_GUI.DrawScore();
}

void Game::HandleInput()
 {
	Event event;
	while (m_renderWindow.pollEvent(event))
	{

		if (event.type == sf::Event::Closed)
			m_renderWindow.close();
		if (event.type == Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case Keyboard::Key::W:
				m_snake.SetDirection(UP);
				break;
			case Keyboard::Key::S:
				m_snake.SetDirection(DOWN);
				break;
			case Keyboard::Key::A:
				m_snake.SetDirection(RIGHT);
				break;
			case Keyboard::Key::D:
				m_snake.SetDirection(LEFT);
				break;
			case Keyboard::Key::Space:
				m_snake.AddSegment();
			default:
				break;
			}
		}
	}
}

void Game::StandardGameLoop()
{
	
	/*RectangleShape background(Vector2f(1024, 1024));
	background.setPosition(0, 0);
	background.setFillColor(Color::Black);*/

	
	Sound sound(AssetManager::GetSoundBuffer("assets\\question.wav"));
	sound.setVolume(20);
	
	m_snake = Snake(SEGMENT_SIZE, HEAD_COLOR, WINDOW_RESOLUTION);
	m_food.setSize(Vector2f(SEGMENT_SIZE.x, SEGMENT_SIZE.y));
	m_food.setFillColor(Color::Blue);
	Vector2f legalFoodPosition = GetLegalFoodPosition(m_snake.GetAllSegmentPositions());
	m_food.setPosition(legalFoodPosition);
	m_food.setTexture(&(AssetManager::GetTexture("assets\\muffin.png")));

	while (m_renderWindow.isOpen()) 
	{
		UpdateClock();
		HandleInput();

		if (m_snake.MoveAlongSnake(m_totalTimeElapsed))
		{
			if (Game::OutOfBoundsLoseState(m_snake.GetLocation())) // checks if head segement is no longer in viewscope
			{
				cout << "out of bounds" << " " << m_snake.GetAllSegmentPositions()[0].x << endl;
				break;
			}
			if (Game::CollisionLoseState(m_snake.GetSegmentsAsReference(), m_snake.GetLocation()))
			{
				cout << "collision detected" << endl;
				//lose text
				break;
			}
			if (Game::FoodCollision(m_food.getPosition(), m_snake.GetAllSegmentPositions()))
			{
				Vector2f legalFoodPosition = GetLegalFoodPosition(m_snake.GetAllSegmentPositions());
				m_food.setPosition(legalFoodPosition);
				m_snake.AddSegment();
				m_GUI.IncrementScore();
				//m_snake.MoveHeadToBack();
				/*m_snake.AdjustRefreshPeriod(0.5);
				speedUpTracker.StartClock();*/

				
				sound.play();
			}
		}
		Clear();
		/*m_renderWindow.draw(background);*/
		Draw(m_snake);
		Display();
	}
}


