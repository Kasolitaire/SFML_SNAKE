#include "Game.h";
#include "SFML//Config.hpp";
int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y), "My window", sf::Style::Close);
    //FloatRect rect(0, 0, 512, 512);
    //View view(rect);
    ////view.zoom(2);
    //renderWindow.setView(view);
    Game Game(renderWindow);
    Game.StartGame();
    return 0;
}