#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x, y;
    float szerokosc, wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float x_, float y_, float szer_, float wys_, float pred_)
        : x(x_), y(y_), szerokosc(szer_), wysokosc(wys_), predkosc(pred_)
    {
        shape.setSize(sf::Vector2f(szerokosc, wysokosc));
        shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    Paletka(const Paletka& other)
        : x(other.x), y(other.y),
        szerokosc(other.szerokosc), wysokosc(other.wysokosc),
        predkosc(other.predkosc), shape(other.shape)
    {
        shape.setPosition(x, y);
    }

    void moveLeft() {
        x -= predkosc;
        shape.setPosition(x, y);
    }

    void moveRight() {
        x += predkosc;
        shape.setPosition(x, y);
    }

    void clampToBounds(float width) {
        if (x - szerokosc / 2.f < 0.f)
            x = szerokosc / 2.f;
        if (x + szerokosc / 2.f > width)
            x = width - szerokosc / 2.f;
        shape.setPosition(x, y);
    }

    void draw(sf::RenderTarget& target) const {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
    float getPredkosc() const { return predkosc; }
    const sf::RectangleShape& getShape() const { return shape; }

    void setPosition(float newX, float newY) {
        x = newX;
        y = newY;
        shape.setPosition(x, y);
    }

    void setPredkosc(float newPredkosc) {
        predkosc = newPredkosc;
    }
};