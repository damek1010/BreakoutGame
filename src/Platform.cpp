#include "Platform.h"

Platform::Platform()
{
    if(!Texture.loadFromFile("img/platform.png")){
        std::cout << "Nie mozna zaladowac tekstury" << std::endl;
    }
    Sprite = sf::Sprite(Texture);
    Sprite.setOrigin(Sprite.getGlobalBounds().width  / 2, Sprite.getGlobalBounds().height / 2);
    Sprite.setPosition(400, 540);

    Speed = 10;
}

Platform::~Platform()
{
    //dtor
}

void Platform::Update(){
    if(ExpandTimer.getElapsedTime().asSeconds() >= 2.f) Sprite.setScale(1, 1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        MoveLeft();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        MoveRight();
    }
}

void Platform::MoveLeft(){
    if(Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2 >= 0)
        Sprite.move(-Speed, 0);
}

void Platform::MoveRight(){
    if(Sprite.getPosition().x + Sprite.getGlobalBounds().width / 2 <= 800)
        Sprite.move(Speed, 0);
}

sf::Vector2f Platform::GetPosition(){
    sf::Vector2f _pos = sf::Vector2f(Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y - Sprite.getGlobalBounds().height / 2);
    return _pos;
}

sf::Vector2f Platform::GetSize(){
    sf::Vector2f Size = sf::Vector2f(Sprite.getGlobalBounds().width, Sprite.getGlobalBounds().height);
    return Size;
}

void Platform::Reset(){
    Sprite.setPosition(400, 540);
}

void Platform::Expand(float x){
    ExpandTimer.restart();
    Sprite.setScale(x, 1);
}
