#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <string>

#include "GameObject.h"

class Platform : public GameObject
{
    public:
        Platform();
        ~Platform();

        void MoveLeft();
        void MoveRight();
        void Reset();
        void Update();

        sf::Vector2f GetPosition();
        sf::Vector2f GetSize();

        sf::Clock ExpandTimer;
        void Expand(float x);

    protected:

    private:
        float Speed;

};

#endif // PLATFORM_H
