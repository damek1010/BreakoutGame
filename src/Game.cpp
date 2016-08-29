#include "Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

int Game::Run(sf::RenderWindow& w)
{
    //this->Window = Window;
    Setup(w);

    while(Window->isOpen())
    {
        if(!GameOver){
            Update();
            if(ReturnCode != -2) return ReturnCode;
        } else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                return S_MENU;
        }
        Draw();
        if(Paused){
            while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){}
            Paused = false;
        }
    }
}

void Game::LoadLevel(int level){
    std::string filename = "maps/map1.txt";
    std::vector<std::vector<int> > Map;
    std::vector<int> tempMap;
    std::ifstream file(filename.c_str());

    bricks.clear();
    platform->Reset();
    Ball* ball = *balls.begin();
    ball->Reset();

    if(file.is_open())
    {
        while(!file.eof())
        {
            std::string str;
            file >> str;

            tempMap.push_back(str[0] - '0');

            if(file.peek() == '\n')
            {
                Map.push_back(tempMap);
                tempMap.clear();
            }
        }
        Map.push_back(tempMap);
    }

    file.close();

    for(int i=0; i<Map.size(); i++)
    {
        for(int j=0; j<Map[i].size(); j++)
        {
            switch(Map[i][j])
            {
            case 0:
                continue;
                break;
            case 1:
            case 2:
            {
                Brick* b = new Brick(Map[i][j]);
                b->SetPosition(sf::Vector2f(j * 70 + 48, i * 36 + 32));
                bricks.push_back(b);
                BricksOnScreen++;
            }
            break;
            }

        }
    }
    Paused = true;
}

void Game::Setup(sf::RenderWindow& w)
{
    balls.clear();
    BackgroundTexture = sf::Texture();
    Background = sf::Sprite();
    ScoreText = sf::Text();
    HeartTexture = sf::Texture();
    GameOverText = sf::Text();
    StartText = sf::Text();

    srand(time(NULL));

    Window = &w; //new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Breakout");
    Window->setFramerateLimit(60);

    ReturnCode = -2;
    CurrentLevel = 1;
    GameOver = false;

    BackgroundTexture.loadFromFile("img/background.png");
    Background = sf::Sprite(BackgroundTexture);
    Background.setScale(800 / Background.getGlobalBounds().width, 600 / Background.getGlobalBounds().height);

    Font.loadFromFile("fonts/monospace.ttf");
    Score = 0;
    ScoreText.setFont(Font);
    ScoreText.setString("Score: " + std::to_string(Score));
    ScoreText.setPosition(5,5);

    StartText.setFont(Font);
    StartText.setString("Press SPACE to start");
    StartText.setPosition(400 - StartText.getGlobalBounds().width / 2, 300 - StartText.getGlobalBounds().height / 2);

    Health = 3;
    HeartTexture.loadFromFile("img/heart.png");
    for(int i=0; i<Health; i++){
        Hearts[i] = sf::Sprite(HeartTexture);
        Hearts[i].setOrigin(Hearts[i].getGlobalBounds().width / 2, Hearts[i].getGlobalBounds().height / 2);
        Hearts[i].setPosition(800 - (i * 34) - 20, 21);
    }

    GameOverText.setFont(Font);
    GameOverText.setString("Game Over");
    GameOverText.setPosition(400 - GameOverText.getGlobalBounds().width / 2, 200);
    GameOverText.setFillColor(sf::Color::Red);

    platform = new Platform();
    Ball* ball = new Ball();
    balls.push_back(ball);

    LoadLevel(CurrentLevel);
}

void Game::Update()
{
    while(Window->pollEvent(event))
    {
        if(event.type == sf::Event::KeyPressed)
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
                ReturnCode = S_MENU;
                break;
            }
        }
    }

    std::list<PowerUp*>::iterator it = powers.begin();
    std::list<PowerUp*>::iterator end = powers.end();
    for(; it != end; it++){
        PowerUp* power = *it;
        if(power->IsOut()){
            powers.erase(it);
            continue;
        }
        if(power->CheckCollision(platform)){
            switch(power->GetID()){
            case 0:
                platform->Expand(2);
                break;
            case 1:
                Ball* b = new Ball();
                b->Reset();
                balls.push_back(b);
                break;
            }
            powers.erase(it);
            continue;
        }
        power->Update();
    }

    platform->Update();
    for(std::list<Ball*>::iterator it = balls.begin(); it != balls.end(); it++){
        Ball* ball = *it;
        ball->Update();
        ball->CheckCollision(*platform);

        if(ball->IsOut()) {
            if(balls.size() <= 1){
                Health--;
                Ball* ball = *balls.begin();
                ball->Reset();
                platform->Reset();
                powers.clear();
                Paused = true;
            } else {
                balls.erase(it);
            }
        }

        for(int i=0; i<bricks.size(); i++)
        {
            if(!bricks[i]->IsActive) continue;
            if(ball->CheckCollision(*bricks[i]) && !bricks[i]->InCollision)
            {
                bricks[i]->InCollision = true;
                bricks[i]->Damage();
                if(!bricks[i]->IsActive){
                    ScoreText.setString("Score: " + std::to_string(++Score));
                    int power = floor(rand() % 4);
                    std::cout << power << std::endl;
                    if(power < 2){
                        PowerUp* p = new PowerUp(power);
                        p->SetPosition(bricks[i]->GetPosition());
                        powers.push_back(p);
                    }
                    BricksOnScreen--;
                }
            }
            else if(bricks[i]->InCollision)
            {
                bricks[i]->InCollision = false;
            }
        }
    }
    if(BricksOnScreen <= 0) LoadLevel(++CurrentLevel);
    if(Health<=0) {
        GameOver = true;
        ScoreText.setPosition(400 - ScoreText.getGlobalBounds().width / 2, 350);
    }
}

void Game::Draw()
{
    Window->clear();

    if(!GameOver){
        Window->draw(Background);
        for(std::list<Ball*>::iterator it = balls.begin(); it != balls.end(); it++){
            Ball* ball = *it;
            Window->draw(*ball);
        }

        for(int i=0; i<bricks.size(); i++)
        {
            if(bricks[i]->IsActive)
            {
                Window->draw(*bricks[i]);
            }
        }
        for(int i=0; i<Health; i++)
            Window->draw(Hearts[i]);
        Window->draw(*platform);

        std::list<PowerUp*>::iterator it = powers.begin();
        std::list<PowerUp*>::iterator end = powers.end();
        for(; it != end; it++){
            PowerUp* power = *it;
            Window->draw(*power);
        }

        Window->draw(ScoreText);
        if(Paused) Window->draw(StartText);
    } else {
        Window->draw(GameOverText);
        Window->draw(ScoreText);
    }

    Window->display();
}
