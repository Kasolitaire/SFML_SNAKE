#include "Game.h";
#include "SFML//Config.hpp";
int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "SFML_SNAKE", sf::Style::Close);
    Game Game(renderWindow);
    Game.StartGame();
    return 0;
}