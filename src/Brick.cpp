#include "Brick.h"

Brick::Brick(int s)
{
    if(!Texture.loadFromFile("img/brick.png")){
        std::cout << "Nie mozna wczytac tekstury klocka" << std::endl;
    }

    TextureOffsetX = (s-1) * 64;

    Sprite = sf::Sprite(Texture, sf::IntRect(TextureOffsetX, 0, 64, 32));
    Sprite.setOrigin(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2);
    Sprite.setPosition(550, 150);

    IsActive = true;
    InCollision = false;

    Shield = s;
}

Brick::~Brick()
{
    //dtor
}

sf::Vector2f Brick::GetPosition(){
    sf::Vector2f _pos = sf::Vector2f(Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y - Sprite.getGlobalBounds().height / 2);
    return _pos;
}

sf::Vector2f Brick::GetSize(){
    sf::Vector2f Size = sf::Vector2f(Sprite.getGlobalBounds().width, Sprite.getGlobalBounds().height);
    return Size;
}

void Brick::SetPosition(sf::Vector2f _pos){
    Sprite.setPosition(_pos);
}

void Brick::Damage(int dmg){
    Shield -= dmg;
    if(Shield <= 0){
        IsActive = false;
    } else {
        TextureOffsetX -= 64;
        Sprite.setTextureRect(sf::IntRect(TextureOffsetX, 0, 64, 32));
    }
}

bool Brick::Contains(sf::Vector2f point){
    if(Sprite.getGlobalBounds().contains(point)) return true;
    return false;
}

int Brick::GetShield(){
    return Shield;
}
