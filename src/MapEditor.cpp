#include "MapEditor.h"
#include <iostream>
#include <fstream>

MapEditor::MapEditor()
{
    //ctor
}

MapEditor::~MapEditor()
{
    //dtor
}

int MapEditor::Run(sf::RenderWindow& w)
{
    Setup(w);

    while(Window->isOpen())
    {
        Update();
        Draw();
    }
}

void MapEditor::Setup(sf::RenderWindow& w)
{
    Window = &w;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<11; j++)
        {
            bricks[j][i] = new Brick();
            bricks[j][i]->SetPosition(sf::Vector2f(j * 70 + 48, i * 36 + 32));
        }
    }
    for(int i=0; i<2; i++)
    {
        samples[i] = new Brick(i+1);
        samples[i]->SetPosition(sf::Vector2f(i * 64 + 336, 500));
    }
    current = new Brick();
    *current = *samples[0];
    current->SetPosition(sf::Vector2f(350, 450));

    noBrick = new Brick(0);
    //current = &*samples[0];
}

void MapEditor::Update()
{
    while(Window->pollEvent(event))
    {
        if(event.type == sf::Event::MouseButtonPressed)
        {
            switch(event.key.code)
            {
            case sf::Mouse::Left:
                for(int i=0; i<2; i++)
                {
                    if(samples[i]->Contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        std::cout << i << std::endl;
                        *current = *samples[i];
                        current->SetPosition(sf::Vector2f(350, 450));
                        break;
                    }
                }
                for(int i=0; i<8; i++)
                {
                    for(int j=0; j<11; j++)
                    {
                        if(bricks[j][i]->Contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        {
                            sf::Vector2f _pos = bricks[j][i]->GetPosition() + sf::Vector2f(bricks[j][i]->GetSize().x / 2, bricks[j][i]->GetSize().y / 2);
                            *bricks[j][i] = *current;
                            bricks[j][i]->SetPosition(_pos);
                        }
                    }
                }
                break;
            case sf::Mouse::Right:
                for(int i=0; i<8; i++)
                {
                    for(int j=0; j<11; j++)
                    {
                        if(bricks[j][i]->Contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        {
                            sf::Vector2f _pos = bricks[j][i]->GetPosition() + sf::Vector2f(bricks[j][i]->GetSize().x / 2, bricks[j][i]->GetSize().y / 2);
                            *bricks[j][i] = *noBrick;
                            bricks[j][i]->SetPosition(_pos);
                        }
                    }
                }
                break;
            }
        }
        if(event.type == sf::Event::KeyPressed)
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Return:
                std::cout << "Zapisywaie..." << std::endl;
                Save();
                break;
            }
        }
    }
}

void MapEditor::Draw()
{
    Window->clear();
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<11; j++)
        {
            Window->draw(*bricks[j][i]);
        }
    }
    for(int i=0; i<2; i++)
        Window->draw(*samples[i]);
    Window->draw(*current);
    Window->display();
}

void MapEditor::Save()
{
    std::fstream file;
    file.open("maps/map.txt", std::ios::out);

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<11; j++)
        {
            file << bricks[j][i]->GetShield();
            if(j<10)
                file << " ";
        }
        file << "\n";
    }

    file.close();
}
