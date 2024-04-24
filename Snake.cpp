#include <iostream>;
#include "Snake.h";
#include "SFML/Window.hpp";
#include "SFML/Graphics.hpp";
using namespace sf;
Snake::Snake()
{
}
Snake::Snake(const Vector2f segmentSize, const Color color, Vector2u windowResolution): //refactor needed
	m_IncrementAmmount(segmentSize.x)
{
	m_SnakeHeadRect.setSize(Vector2f(segmentSize.x, segmentSize.y));
	m_SnakeHeadRect.setFillColor(color);
	m_SnakeHeadRect.setOutlineColor(Color::Yellow);
	m_SnakeHeadRect.setOutlineThickness(2);
	m_SnakeHeadRect.setPosition(windowResolution.x / 2, windowResolution.y / 2); //sets player to center of screen
}
Snake::~Snake()
{
	for (int i = 0; i < m_SnakeSegmentsRect.size(); i++) 
	{
		delete m_SnakeSegmentsRect[i];
	}
}
;
bool Snake::DrawHeadSegment(RenderWindow& renderWindow)
{
	renderWindow.draw(m_SnakeHeadRect);
	return true;
}

void Snake::SetDirection(Direction desiredDirection)
{
	switch (desiredDirection)
	{
	case UP:
		if (m_currentDirection != DOWN)
			m_desiredDirection = desiredDirection;
		break;
	case DOWN:
		if (m_currentDirection != UP)
			m_desiredDirection = desiredDirection;
		break;
	case LEFT:
		if (m_currentDirection != RIGHT)
			m_desiredDirection = desiredDirection;
		break;
	case RIGHT:
		if (m_currentDirection != LEFT)
			m_desiredDirection = desiredDirection;
		break;
	}
}
RectangleShape* Snake::CreateSegment()
{
	RectangleShape* p_newSegment = new RectangleShape(SEGMENT_SIZE);
	p_newSegment->setFillColor(Color::Green);
	p_newSegment->setOutlineColor(Color::Cyan);
	p_newSegment->setOutlineThickness(2);// not the greatest no option to change color seperate from head
	return p_newSegment;
}
bool Snake::MoveHeadSegmentSetPeriod(const Time& totalTimeElapsed)
{
	Time timeElapsed = totalTimeElapsed - m_previousMovementTimeStamp;

	if (timeElapsed.asSeconds() > m_TimeToMoveSeconds)
	{
		m_PreviousHeadPosition = m_SnakeHeadRect.getPosition();
		switch (m_desiredDirection) 
		{
		case UP:
			m_SnakeHeadRect.move(0, -m_IncrementAmmount);
			m_previousMovementTimeStamp = totalTimeElapsed;
			m_currentDirection = m_desiredDirection;
			return true;
		case DOWN:
			m_SnakeHeadRect.move(0, m_IncrementAmmount);
			m_previousMovementTimeStamp = totalTimeElapsed;
			m_currentDirection = m_desiredDirection;
			return true;
		case LEFT:
			m_SnakeHeadRect.move(m_IncrementAmmount, 0);
			m_previousMovementTimeStamp = totalTimeElapsed;
			m_currentDirection = m_desiredDirection;
			return true;
		case RIGHT:
			m_SnakeHeadRect.move(-m_IncrementAmmount, 0);
			m_previousMovementTimeStamp = totalTimeElapsed;
			m_currentDirection = m_desiredDirection;
			return true;
		}
	}
	return false;
}

void Snake::AddSegment() // refactor needed
{
	m_SnakeSegmentsRect.push_back(CreateSegment());
	if (m_SnakeSegmentsRect.size() == 1)
	{
		m_SnakeSegmentsRect[0]->setPosition(m_PreviousHeadPosition);
	}
	else 
	{
		m_SnakeSegmentsRect.back()->setPosition(m_previousPositionLastSegment); // just terrible
	}
	std::cout << "Segment added" << std::endl;
	/*for (int i = 0; i < m_SnakeSegmentsRect.size(); i++) 
	{
		std::cout << m_SnakeSegmentsRect[0].getPosition().x << m_SnakeSegmentsRect.size() <<std::endl;
	}*/
}

bool Snake::MoveAlongSnake(Time& totalTimeElapsed)
{
	if (MoveHeadSegmentSetPeriod(totalTimeElapsed))
	{
		MoveAlongSegments();
		return true;
	}
	else
		return false;
}

void Snake::MoveAlongSegments() 
{
	Vector2f lastPosition = m_PreviousHeadPosition;
	for (int i = 0; i < m_SnakeSegmentsRect.size(); i++) 
	{
		Vector2f tempPosition =  m_SnakeSegmentsRect[i]->getPosition();
		m_SnakeSegmentsRect[i]->setPosition(lastPosition);
		lastPosition = tempPosition;
	}
	m_previousPositionLastSegment = lastPosition;
}

Vector2f Snake::GetLocation()
{
	return m_SnakeHeadRect.getPosition();
}

vector<RectangleShape*>& Snake::GetSegmentsAsReference()
{
	return m_SnakeSegmentsRect;
}

vector<Vector2f> Snake::GetAllSegmentPositions()
{
	vector<Vector2f> segmentPositions;
	segmentPositions.push_back(m_SnakeHeadRect.getPosition());
	//cout << segmentPositions[0].x << " " << segmentPositions[0].y << endl;

	for (int i = 0; i < m_SnakeSegmentsRect.size(); i++) 
	{
		segmentPositions.push_back(m_SnakeSegmentsRect[i]->getPosition());
		//cout << segmentPositions[i+1].x << " " << segmentPositions[i+1].y << endl;
	}
	
	return segmentPositions;
}

void Snake::MoveHeadToBack()
{
	if (m_SnakeSegmentsRect.size() > 0) 
	{
		m_SnakeHeadRect.setPosition(m_SnakeSegmentsRect.back()->getPosition());
		m_PreviousHeadPosition = m_SnakeHeadRect.getPosition();
		MoveAlongSegments();
		ReverseSegments();
	}
	switch (m_currentDirection)
	{
	case UP:
		m_currentDirection = DOWN;
		m_desiredDirection = DOWN;
		break;
	case DOWN:
		m_currentDirection = UP;
		m_desiredDirection = UP;

		break;
	case LEFT:
		m_currentDirection = RIGHT;
		m_desiredDirection = RIGHT;
		break;
	case RIGHT:
		m_currentDirection = LEFT;
		m_desiredDirection = LEFT;
		break;
	default:
		break;
	}
}

void Snake::DrawSegments(RenderWindow& renderWindow)
{
	for (int i = 0; i < m_SnakeSegmentsRect.size(); i++) 
	{
		renderWindow.draw(*m_SnakeSegmentsRect[i]);
	}
}

void Snake::MultiplyRefreshPeriod(const float refreshMultiplier)
{
	m_TimeToMoveSeconds = m_TimeToMoveSeconds * refreshMultiplier;
}

void Snake::ReturnRefreshPeriodToDefault()
{
	m_TimeToMoveSeconds = m_defaultRefreshPeriod;
}

void Snake::ReverseSegments()
{
	vector<RectangleShape*> p_segments;
	for (int i = m_SnakeSegmentsRect.size() - 1; i >= 0; i--)
	{
		p_segments.push_back(m_SnakeSegmentsRect[i]);
		cout << m_SnakeSegmentsRect[i]->getPosition().x << " " << m_SnakeSegmentsRect[i]->getPosition().y << endl;
	}
	cout << "space" << endl;
	for (int i = 0; i < m_SnakeSegmentsRect.size(); i++) 
	{
		m_SnakeSegmentsRect[i] = p_segments[i];
		cout << m_SnakeSegmentsRect[i]->getPosition().x << " " << m_SnakeSegmentsRect[i]->getPosition().y << endl;
	}
}

