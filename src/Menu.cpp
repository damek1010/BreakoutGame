#include "Menu.h"

Menu::Menu()
{
    DoSetup = true;
}

Menu::~Menu()
{
    //dtor
}

int Menu::Run(sf::RenderWindow& w){
    if(DoSetup) Setup(w);
    ReturnCode = -2;

    while(Window->isOpen()){
        Update();
        if(ReturnCode != -2) return ReturnCode;
        Draw();
    }
}

void Menu::Setup(sf::RenderWindow& w){
    Window = &w;

    Pointer = 0;
    ReturnCode = -2;

    std::string str[] = {"Start Game", "Map Editor", "Exit"};
    OptionCount = 3;

    Font.loadFromFile("fonts/monospace.ttf");
    for(int i=0; i<OptionCount; i++){
        Text[i].setFont(Font);
        Text[i].setString(str[i]);
        Text[i].setPosition(400 - Text[i].getGlobalBounds().width / 2, 180 + i * 80);
    }
    Text[Pointer].setFillColor(sf::Color::Blue);

    DoSetup = false;
}

void Menu::Update(){
    while(Window->pollEvent(event)){
        if(event.type == sf::Event::KeyPressed){
            switch(event.key.code){
            case sf::Keyboard::W:
                if(Pointer > 0)
                    Pointer--;
                break;
            case sf::Keyboard::S:
                if(Pointer < OptionCount - 1)
                    Pointer++;
                break;
            case sf::Keyboard::Return:
                switch(Pointer){
                case 0:
                    ReturnCode = S_GAME;
                    break;
                case 1:
                    ReturnCode = S_MAPEDITOR;
                    break;
                case 2:
                    ReturnCode = S_EXIT;
                    break;
                }
                break;
            }
            for(int i=0; i<OptionCount; i++)
                Text[i].setFillColor(sf::Color::White);

            Text[Pointer].setFillColor(sf::Color::Blue);
        }
    }
}

void Menu::Draw(){
    Window->clear();
    for(int i=0; i<OptionCount; i++)
        Window->draw(Text[i]);
    Window->display();
}
