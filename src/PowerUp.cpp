#include "PowerUp.h"

PowerUp::PowerUp(int id)
{
    Texture.loadFromFile("img/powerups.png");
    Sprite = sf::Sprite(Texture, sf::IntRect(id * 16, 0, 16, 16));
    Sprite.setOrigin(Sprite.getGlobalBounds().width  / 2, Sprite.getGlobalBounds().height / 2);
    Sprite.setPosition(100, 0);

    ID = id;
    Speed = 5.f;
}

PowerUp::~PowerUp()
{
    //dtor
}

void PowerUp::Update(){
    Sprite.move(0, Speed);
}

bool PowerUp::IsOut(){
    if(Sprite.getPosition().y > 600) return true;
    return false;
}

bool PowerUp::CheckCollision(Platform* platform){
    float x1 = Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2;
    float x2 = Sprite.getPosition().x + Sprite.getGlobalBounds().width / 2;
    float y = Sprite.getPosition().y + Sprite.getGlobalBounds().height / 2;

    sf::IntRect boundingBox = sf::IntRect(platform->GetPosition().x, platform->GetPosition().y, platform->GetSize().x, platform->GetSize().y);
    if(boundingBox.contains(x1, y) ||
    boundingBox.contains(x2, y) ||
    boundingBox.contains(Sprite.getPosition().x, y) ||
    boundingBox.contains(x1, Sprite.getPosition().y) ||
    boundingBox.contains(x2, Sprite.getPosition().y) ||
    boundingBox.contains(Sprite.getPosition().x, Sprite.getPosition().y)){
        return true;
    }
    return false;
}

int PowerUp::GetID(){
    return ID;
}
