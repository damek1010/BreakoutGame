#include "Ball.h"

Ball::Ball()
{
    if(!Texture.loadFromFile("img/ball.png")){
        std::cout << "Nie mozna zaladowac tekstury pilki" << std::endl;
    }
    Sprite = sf::Sprite(Texture);
    Sprite.setOrigin(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2);
    Sprite.setPosition(400, 450);

    srand(time(NULL));
    MaxSpeed = 4.5f;

    /*SpeedX = 3;
    SpeedY = 3;
    turnX = LEFT;
    turnY = DOWN;*/
}

Ball::~Ball()
{
    //dtor
}

void Ball::Update(){
    if(Sprite.getPosition().x + Sprite.getGlobalBounds().width > 800 || Sprite.getPosition().x - Sprite.getGlobalBounds().width < 0)
        turnX = (turnX == LEFT) ? RIGHT : LEFT;

    if(Sprite.getPosition().y - Sprite.getGlobalBounds().height < 0)
        turnY = (turnY == UP) ? DOWN : UP;

    float x = (turnX == LEFT) ? -SpeedX : SpeedX;
    float y = (turnY == UP) ? -SpeedY : SpeedY;
    Sprite.move(x, y);
}

bool Ball::CheckCollision(Platform platform){
    float x = (turnX == LEFT) ? Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2 : Sprite.getPosition().x + Sprite.getGlobalBounds().width / 2;
    float y = (turnY == UP) ? Sprite.getPosition().y - Sprite.getGlobalBounds().height / 2: Sprite.getPosition().y + Sprite.getGlobalBounds().height / 2;

    sf::FloatRect boundingBox = sf::FloatRect(platform.GetPosition().x, platform.GetPosition().y, platform.GetSize().x, platform.GetSize().y);
    if(boundingBox.contains(x, y)){
        if(x > boundingBox.left && x < boundingBox.left + boundingBox.width)
            turnY = UP;
        else
            turnX = (turnX == LEFT) ? RIGHT : LEFT;
        return true;
    }
    return false;
}

bool Ball::CheckCollision(Brick brick){
    float x = (turnX == LEFT) ? Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2 : Sprite.getPosition().x + Sprite.getGlobalBounds().width / 2;
    float y = (turnY == UP) ? Sprite.getPosition().y - Sprite.getGlobalBounds().height / 2: Sprite.getPosition().y + Sprite.getGlobalBounds().height / 2;

    sf::FloatRect boundingBox = sf::FloatRect(brick.GetPosition().x, brick.GetPosition().y, brick.GetSize().x, brick.GetSize().y);
    if(boundingBox.contains(x, y)
       || boundingBox.contains(Sprite.getPosition().x, y)
       || boundingBox.contains(x, Sprite.getPosition().y)){
        if(Sprite.getPosition().x > boundingBox.left && Sprite.getPosition().x < boundingBox.left + boundingBox.width)
            turnY = (turnY == UP) ? DOWN : UP;
        else
            turnX = (turnX == LEFT) ? RIGHT : LEFT;
        return true;
    }
    return false;
}

bool Ball::IsOut(){
    if(Sprite.getPosition().y > 580) return true;
    return false;
}

void Ball::Reset(){
    Sprite.setPosition(400, 350);
    SpeedX = rand() % 8 - 4;
    SpeedY = sqrt(pow(MaxSpeed, 2) - pow(SpeedX, 2));

    turnX = (SpeedX < 0) ? LEFT : RIGHT;
    turnY = DOWN;

    SpeedX = abs(SpeedX);
    SpeedY = abs(SpeedY);

    /*SpeedX = rand() % 8 - 4;
    SpeedY = sqrt(pow(MaxSpeed, 2) - pow(SpeedX, 2));*/
}
