#pragma once
#include <string>;
#include "SFML/Graphics.hpp"
using namespace sf;

const Vector2u WINDOW_RESOLUTION(800, 800);
const Color HEAD_COLOR = Color::Green;
const Color SEGMENT_COLOR = Color::Yellow;
const Vector2f SEGMENT_SIZE(25, 25);
const float REFRESH_PERIOD = 0.1f;
const String FONT_PATH = "assets\\Vermin Vibes 1989.ttf";
const String GUIOptions[2] = { "PLAY", "EXIT" };
const int SCORE_INCREMENT = 50;
