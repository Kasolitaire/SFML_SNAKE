#include "GUI.h"


bool GUI::CheckForHover(Text& text)
{
	Vector2i mousePos = Mouse::getPosition(r_renderWindow);
	Vector2f textPos = text.getGlobalBounds().getPosition();

	if (
		(mousePos.x >= textPos.x && mousePos.x <= textPos.x + text.getGlobalBounds().getSize().x)
		&& (mousePos.y >= textPos.y && mousePos.y <= textPos.y + text.getGlobalBounds().getSize().y)
		) 
	{
		text.setFillColor(sf::Color::Red);
		return true;
	}
	else 
	{
		text.setFillColor(sf::Color::White);
	}
	return false;
}

void GUI::OnHover()
{
}

void GUI::DrawText()
{
	for (int i = 0; i < m_GUIText.size(); i++) 
	{
		r_renderWindow.draw(m_GUIText[i]);
	}
}

GUI::GUI(RenderWindow& renderWindow) : r_renderWindow(renderWindow)
{
	
	
	m_font.loadFromFile(FONT_PATH);

	m_scoreText.setCharacterSize(50); // in pixels, not points!
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(50, 0); // maybe should be coordintaes should be global
	m_scoreText.setString("SCORE 0");
	m_scoreText.setFont(m_font);

	for (string option : GUIOptions) 
	{
		m_GUIText.push_back(Text());
		m_GUIText.back().setFont(m_font);
		m_GUIText.back().setString(option);
		m_GUIText.back().setFillColor(Color::White);
		m_GUIText.back().setCharacterSize(SEGMENT_SIZE.x);
	}

	m_GUIText[0].setPosition(WINDOW_RESOLUTION.x / 2, WINDOW_RESOLUTION.y / 2);
	m_GUIText[1].setPosition(WINDOW_RESOLUTION.x / 2, WINDOW_RESOLUTION.y / 2 + 50); //needs to be put elsewhere...
}

bool GUI::CheckForPlay()
{
	if (CheckForHover(m_GUIText[0]) && Mouse::isButtonPressed(Mouse::Button::Left))
		return true;
	else
		return false;
}

bool GUI::CheckForExit()
{
	if (CheckForHover(m_GUIText[1]) && Mouse::isButtonPressed(Mouse::Button::Left))
		return true;
	else
		return false;
}

void GUI::IncrementScore()
{
	m_score += SCORE_INCREMENT;
	m_scoreText.setString("SCORE " + to_string(m_score));
}

void GUI::ScoreReset()
{
	m_score = 0;
	m_scoreText.setString("SCORE " + to_string(m_score));
}

void GUI::DrawScore()
{
	r_renderWindow.draw(m_scoreText);
}
