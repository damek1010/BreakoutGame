#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>
#include <string>

#include "Screen.h"
#include "PowerUp.h"
#include "Platform.h"
#include "Ball.h"

class Game : public Screen
{
    public:
        virtual int Run(sf::RenderWindow&);

        Game();

    protected:

    private:

        Game(Game const&);
        //Game operator=(const Game);
        ~Game();

        void LoadLevel(int);
        void Setup(sf::RenderWindow&);
        void Update();
        void Draw();

        sf::RenderWindow* Window;
        sf::Event event;
        sf::Texture BackgroundTexture;
        sf::Sprite Background;

        int Health;
        sf::Texture HeartTexture;
        sf::Sprite Hearts[3];
        sf::Text GameOverText;

        int Score;
        sf::Font Font;
        sf::Text ScoreText;
        sf::Text StartText;

        Platform* platform;
        std::list<Ball*> balls;
        std::vector<Brick*> bricks;
        std::list<PowerUp*> powers;

        int BricksOnScreen;
        int CurrentLevel;
        int ReturnCode;
        bool Paused;
        bool GameOver;
};

#endif // GAME_H
