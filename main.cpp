#include "GameLogic.h";
#include "SFML//Config.hpp"
int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y), "My window", sf::Style::Close);
    GameLogic gameLogic(renderWindow);
    gameLogic.StartGame();
    return 0;
}