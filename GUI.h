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
const string REVERSE_BUTTON = "REVERSE_BUTTON";
const string SPEED_BUTTON = "SPEED_BUTTON";
const string VOLUME_BUTTON = "VOLUME_BUTTON";
class GUI
{
public:
	bool CheckForHover(Text& text);
	void OnHover(Text& text);
	void OnHoverExit(Text& text);
	void DrawOptions(); //draws everything but the score
	GUI(RenderWindow& renderWindow);
	bool m_GUIOpen = true;
	bool CheckForPlay();
	bool CheckForExit();
	void IncrementScore();
	void ScoreReset();
	void DrawScore();
	bool CheckForButton(const string& buttonType);
	Text CreateTextOption(const string& content, const Font& font, Color color, const unsigned int& size);
private:
	unordered_map<string, Text> m_GUITextMap;
	RenderWindow& r_renderWindow;
	int m_score = 0;
};

