#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Global.h";
#include <iostream>;
#include <string>
#include <vector>
#include "Snake.h";
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
private:
	String m_GUIOptions[2] = {"PLAY", "EXIT"};
	Font m_font;
	vector<Text> m_GUIText;
	Text m_scoreText;
	RenderWindow& r_renderWindow;
	int m_score = 0;
};

