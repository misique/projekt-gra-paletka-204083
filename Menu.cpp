#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Blad: Nie mozna zaladowac czcionki!\n";
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }

    sf::Text t;

    t.setFont(font);
    t.setFillColor(sf::Color::Cyan);
    t.setString("Nowa gra");
    t.setCharacterSize(40);
    t.setStyle(sf::Text::Bold);
    t.setPosition(sf::Vector2f(width / 3.f, height / 5.f * 1.f));
    menu.push_back(t);

    t.setFillColor(sf::Color::White);
    t.setString("Wczytaj gre");
    t.setStyle(sf::Text::Regular);
    t.setPosition(sf::Vector2f(width / 3.f, height / 5.f * 2.f));
    menu.push_back(t);

    t.setString("Ostatnie wyniki");
    t.setPosition(sf::Vector2f(width / 3.f, height / 5.f * 3.f));
    menu.push_back(t);

    t.setString("Wyjscie");
    t.setPosition(sf::Vector2f(width / 3.f, height / 5.f * 4.f));
    menu.push_back(t);

    selectedItem = 0;
    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void Menu::draw(sf::RenderWindow& window)
{
    for (auto& m : menu)
        window.draw(m);
}

void Menu::przesunG()
{
    if (menu.empty()) return;

    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);

    selectedItem--;
    if (selectedItem < 0)
        selectedItem = menu.size() - 1;

    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void Menu::przesunD()
{
    if (menu.empty()) return;

    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);

    selectedItem++;
    if (selectedItem >= menu.size())
        selectedItem = 0;

    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}