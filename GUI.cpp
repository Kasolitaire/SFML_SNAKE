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
		return true;
	}
	return false;
}

void GUI::OnHover(Text& text)
{
	text.setFillColor(sf::Color::Red);
}

void GUI::OnHoverExit(Text& text)
{
	text.setFillColor(sf::Color::White);
}

void GUI::DrawOptions()
{
	for (auto& iter : m_GUITextMap) 
	{
		if(iter.first != "SCORE")
			r_renderWindow.draw(iter.second);
	}
}

GUI::GUI(RenderWindow& renderWindow) : r_renderWindow(renderWindow)
{
	Font& font = AssetManager::GetFont(FONT_PATH);
	
	m_GUITextMap["PLAY"] = CreateTextOption("PLAY", font, Color::White, 50);
	m_GUITextMap["EXIT"] = CreateTextOption("EXIT", font, Color::White, 50);
	m_GUITextMap["SCORE"] = CreateTextOption("SCORE 0", font, Color::White, 50);
	m_GUITextMap[SPEED_BUTTON] = CreateTextOption("SPEED MODIFIER", font, Color::White, 50);
	m_GUITextMap[REVERSE_BUTTON] = CreateTextOption("REVERSE MODIFIER", font, Color::White, 50);
	
	m_GUITextMap["PLAY"].setPosition(WINDOW_RESOLUTION.x / 2, WINDOW_RESOLUTION.y / 2);
	m_GUITextMap["EXIT"].setPosition(WINDOW_RESOLUTION.x / 2, WINDOW_RESOLUTION.y / 2 + 50);
	m_GUITextMap["SCORE"].setPosition(100, 0);
	m_GUITextMap[SPEED_BUTTON].setPosition(500, 0);
	m_GUITextMap[REVERSE_BUTTON].setPosition(700, 0);
}

bool GUI::CheckForPlay()
{
	if (CheckForHover(m_GUITextMap["PLAY"])) 
	{
		OnHover(m_GUITextMap["PLAY"]);
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			return true;
	}
	else
		OnHoverExit(m_GUITextMap["PLAY"]);
	return false;
}

bool GUI::CheckForExit()
{
	if (CheckForHover(m_GUITextMap["EXIT"]))
	{
		OnHover(m_GUITextMap["EXIT"]);
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			return true;
	}
	else
		OnHoverExit(m_GUITextMap["EXIT"]);
	return false;
}

void GUI::IncrementScore()
{
	m_score += SCORE_INCREMENT;
	m_GUITextMap["SCORE"].setString("SCORE " + to_string(m_score));
}

void GUI::ScoreReset()
{
	m_score = 0;
	m_GUITextMap["SCORE"].setString("SCORE " + to_string(m_score));
}

void GUI::DrawScore()
{
	r_renderWindow.draw(m_GUITextMap["SCORE"]);
}

bool GUI::CheckForButton(const string& buttonType)
{
	if (CheckForHover(m_GUITextMap[buttonType])) //is button pressed not ideal need on release or bool
	{
		cout << "clicked";
		Color color = m_GUITextMap[buttonType].getFillColor();
		if (color == Color::White)
			color = Color::Red;
		else color = Color::White;
		m_GUITextMap[buttonType].setFillColor(color);
		return true;
	}
	return false;
}

Text GUI::CreateTextOption(const string& content, const Font& font, Color color, const unsigned int& size)
{
	Text text;
	text.setFont(font);
	text.setString(content);
	text.setFillColor(color);
	text.setCharacterSize(size);
	Vector2f textSize = text.getGlobalBounds().getSize();
	
	//can become blurry if not rounded
	textSize.x = round(textSize.x / 2);
	textSize.y = round(textSize.y / 2); 
	
	text.setOrigin(textSize);
	return text;
}
