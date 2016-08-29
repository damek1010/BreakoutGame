#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Screen.h"

class Menu : public Screen
{
    public:
        Menu();
        ~Menu();

        virtual int Run(sf::RenderWindow&);

    protected:

    private:
        void Setup(sf::RenderWindow&);
        void Update();
        void Draw();

        sf::RenderWindow* Window;
        sf::Event event;
        sf::Font Font;
        sf::Text Text[3];

        int OptionCount;
        int ReturnCode;
        int Pointer;

        bool DoSetup;
};

#endif // MENU_H
