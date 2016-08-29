#ifndef POWERUP_H
#define POWERUP_H

#include <string>

#include "GameObject.h"
#include "Platform.h"

class PowerUp : public GameObject
{
    public:
        PowerUp(int id);
        ~PowerUp();

        bool CheckCollision(Platform*);

        bool IsOut();
        void Update();

        int GetID();
    protected:

    private:
        int ID;
        float Speed;
};

#endif // POWERUP_H
