#include "GameObject.h"

GameObject::GameObject()
{
    //ctor
}

GameObject::~GameObject()
{
    //dtor
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(Sprite);
    if(Debug){
        sf::Vertex line1[] = {
            sf::Vertex(sf::Vector2f(Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y - Sprite.getGlobalBounds().height / 2)),
            sf::Vertex(sf::Vector2f(Sprite.getPosition().x + Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y - Sprite.getGlobalBounds().height / 2))
            };
        sf::Vertex line2[] = {
            sf::Vertex(sf::Vector2f(Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y - Sprite.getGlobalBounds().height / 2)),
            sf::Vertex(sf::Vector2f(Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y + Sprite.getGlobalBounds().height / 2))
            };
        sf::Vertex line3[] = {
            sf::Vertex(sf::Vector2f(Sprite.getPosition().x - Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y + Sprite.getGlobalBounds().height / 2)),
            sf::Vertex(sf::Vector2f(Sprite.getPosition().x + Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y + Sprite.getGlobalBounds().height / 2))
            };
        sf::Vertex line4[] = {
            sf::Vertex(sf::Vector2f(Sprite.getPosition().x + Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y - Sprite.getGlobalBounds().height / 2)),
            sf::Vertex(sf::Vector2f(Sprite.getPosition().x + Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y + Sprite.getGlobalBounds().height / 2))
            };
        target.draw(line1, 2, sf::Lines);
        target.draw(line2, 2, sf::Lines);
        target.draw(line3, 2, sf::Lines);
        target.draw(line4, 2, sf::Lines);
    }
}

sf::Vector2f GameObject::GetPosition(){
    return Sprite.getPosition();
}

void GameObject::SetPosition(sf::Vector2f _pos){
    Sprite.setPosition(_pos);
}

sf::Vector2f GameObject::GetSize(){
    return sf::Vector2f(Sprite.getGlobalBounds().width, Sprite.getGlobalBounds().height);
}
