#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <string>

#include "GameObject.h"
#include "Platform.h"
#include "Brick.h"

enum Turn{
    UP, RIGHT, DOWN, LEFT
};

class Ball : public GameObject
{
    public:
        Ball();
        ~Ball();

        bool CheckCollision(Platform);
        bool CheckCollision(Brick);
        void Update();
        void Reset();
        bool IsOut();

    protected:

    private:
        float MaxSpeed;
        float SpeedX;
        float SpeedY;

        Turn turnX = RIGHT, turnY = DOWN;

};

#endif // BALL_H
