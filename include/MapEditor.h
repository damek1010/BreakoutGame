#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <string>

#include "Screen.h"
#include "Brick.h"

class MapEditor : public Screen
{
    public:
        MapEditor();
        ~MapEditor();

        virtual int Run(sf::RenderWindow&);
    protected:

    private:
        void Setup(sf::RenderWindow&);
        void Update();
        void Draw();
        void Save();

        sf::RenderWindow* Window;
        sf::Event event;

        Brick* bricks[11][8];
        Brick* samples[2];
        Brick* current;
        Brick* noBrick;
};

#endif // MAPEDITOR_H
