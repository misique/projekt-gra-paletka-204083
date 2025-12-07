#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape
{
private:
    int m_punktyZycia;
    bool m_jestZniszczony;

    static const std::array<sf::Color, 4> colorLUT;

    void aktualizujKolor()
    {
        if (m_punktyZycia >= 0 && m_punktyZycia < (int)colorLUT.size())
            this->setFillColor(colorLUT[m_punktyZycia]);
    }

public:
    Stone(sf::Vector2f pos, sf::Vector2f size, int L)
        : m_punktyZycia(L), m_jestZniszczony(false)
    {
        this->setPosition(pos);
        this->setSize(size);
        this->setOutlineThickness(2.f);
        this->setOutlineColor(sf::Color::Black);
        aktualizujKolor();
    }

    static Stone createFromData(float x, float y, float width, float height, int hp) {
        Stone stone(sf::Vector2f(x, y), sf::Vector2f(width, height), hp);
        stone.setHP(hp); 
        return stone;
    }

    void hit()
    {
        if (m_jestZniszczony) return;
        m_punktyZycia--;
        if (m_punktyZycia <= 0)
            m_jestZniszczony = true;

        aktualizujKolor();
    }

    bool isDestroyed() const { return m_jestZniszczony; }
    int getHP() const { return m_punktyZycia; }
    void setHP(int hp) {
        m_punktyZycia = hp;
        m_jestZniszczony = (hp <= 0);
        aktualizujKolor();
    }

    sf::Vector2f getPos() const { return this->getPosition(); }
};