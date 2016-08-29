#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>

class GameObject : public sf::Drawable
{
    public:
        GameObject();
        ~GameObject();

        bool IsActive;

        virtual void Update(){}

        sf::Vector2f GetPosition();
        sf::Vector2f GetSize();

        void SetPosition(sf::Vector2f);

    protected:
        bool Debug = false;

        sf::Sprite Sprite;
        sf::Texture Texture;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void Reset(){}

    private:

};

#endif // GAMEOBJECT_H
