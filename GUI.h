#pragma once
#include "SFML/Window.hpp";
#include "SFML/Graphics.hpp";
#include "Global.h";
#include <iostream>;
#include <string>;
#include <vector>;
#include <unordered_map>;
#include "Snake.h";
#include "AssetManager.h";
using namespace std;
using namespace sf;
class GUI
{
public:
	bool CheckForHover(Text& text);
	void OnHover();
	void DrawText();
	GUI(RenderWindow& renderWindow);
	bool m_GUIOpen = true;
	bool CheckForPlay();
	bool CheckForExit();
	void IncrementScore();
	void ScoreReset();
	void DrawScore();
	Text CreateTextOption(const string& content, const Font& font, Color color, const unsigned int& size);
private:
	unordered_map<string, Text> m_GUITextMap;
	Text m_scoreText;
	RenderWindow& r_renderWindow;
	int m_score = 0;
};

