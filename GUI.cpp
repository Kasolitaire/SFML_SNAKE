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
	
	for (auto& iter : m_GUITextMap) 
	{
		r_renderWindow.draw(iter.second);
	}
}

GUI::GUI(RenderWindow& renderWindow) : r_renderWindow(renderWindow)
{
	Font& font = AssetManager::GetFont(FONT_PATH);
	
	m_scoreText.setCharacterSize(50); // in pixels, not points!
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(50, 0); // maybe should be coordintaes should be global
	m_scoreText.setString("SCORE 0");
	m_scoreText.setFont(font);

	m_GUITextMap["PLAY"] = CreateTextOption("PLAY", font, Color::White, 50);
	m_GUITextMap["EXIT"] = CreateTextOption("EXIT", font, Color::White, 50);
	
	m_GUITextMap["PLAY"].setPosition(WINDOW_RESOLUTION.x / 2, WINDOW_RESOLUTION.y / 2);
	m_GUITextMap["EXIT"].setPosition(WINDOW_RESOLUTION.x / 2, WINDOW_RESOLUTION.y / 2 + 50);
}

bool GUI::CheckForPlay()
{
	if (CheckForHover(m_GUITextMap["PLAY"]) && Mouse::isButtonPressed(Mouse::Button::Left))
		return true;
	else
		return false;
}

bool GUI::CheckForExit()
{
	if (CheckForHover(m_GUITextMap["EXIT"]) && Mouse::isButtonPressed(Mouse::Button::Left))
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

Text GUI::CreateTextOption(const string& content, const Font& font, Color color, const unsigned int& size)
{
	Text text;
	text.setFont(font);
	text.setString(content);
	text.setFillColor(color);
	text.setCharacterSize(size);
	return text;
}
