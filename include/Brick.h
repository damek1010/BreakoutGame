#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "GameObject.h"

class Brick : public GameObject
{
    public:
        Brick(int s = 1);
        ~Brick();

        //bool Draw;
        bool InCollision;

        int GetShield();
        sf::Vector2f GetPosition();
        sf::Vector2f GetSize();

        void SetPosition(sf::Vector2f);
        void Damage(int dmg = 1);

        bool Contains(sf::Vector2f);

    protected:

    private:
        int Shield;
        int TextureOffsetX;
};

#endif // BRICK_H
