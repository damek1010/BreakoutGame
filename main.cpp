#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include <string>

#include "Menu.h"
#include "Game.h"
#include "MapEditor.h"

using namespace std;

int main()
{
    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Breakout");
    Window.setFramerateLimit(60);

    int screen = 0;

    Menu* clearMenu = new Menu();
    Game* clearGame = new Game();
    MapEditor* ClearMapEditor = new MapEditor();

    vector<Screen*> ClearScreens;

    ClearScreens.push_back(clearMenu);
    ClearScreens.push_back(clearGame);
    ClearScreens.push_back(ClearMapEditor);

    Menu* menu = new Menu();
    Game* game = new Game();
    MapEditor* mapEditor = new MapEditor();

    vector<Screen*> screens;
    screens.push_back(menu);
    screens.push_back(game);
    screens.push_back(mapEditor);

    while(screen >= 0){
        int prevScreen = screen;
        screen = screens[screen]->Run(Window);
        *screens[prevScreen] = *ClearScreens[prevScreen];
    }

    return 0;
}
