#include "Game.h";
#include "SFML//Config.hpp";
int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y), "My window", sf::Style::Close);
    Game Game(renderWindow);
    Game.StartGame();
    return 0;
}