#ifndef SCREEN_H
#define SCREEN_H

#define S_MENU 0
#define S_GAME 1
#define S_MAPEDITOR 2
#define S_EXIT -1

#include <SFML/Graphics.hpp>
#include <string>

class Screen
{
    public:
        Screen();
        ~Screen();

        virtual int Run(sf::RenderWindow&)=0;

    protected:

    private:
};

#endif // SCREEN_H
