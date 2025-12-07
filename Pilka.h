#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Paletka;
class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float x_, float y_, float vx_, float vy_, float r_)
        : x(x_), y(y_), vx(vx_), vy(vy_), radius(r_)
    {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    Pilka(const Pilka& other)
        : x(other.x), y(other.y), vx(other.vx), vy(other.vy),
        radius(other.radius), shape(other.shape)
    {
        shape.setPosition(x, y);
    }

    void move() {
        x += vx;
        y += vy;
        shape.setPosition(x, y);
    }

    void bounceX() { vx = -vx; }
    void bounceY() { vy = -vy; }

    void collideWalls(float width, float height) {
        if (x - radius <= 0.f) {
            x = radius;
            bounceX();
        }
        else if (x + radius >= width) {
            x = width - radius;
            bounceX();
        }

        if (y - radius <= 0.f) {
            y = radius;
            bounceY();
        }
        shape.setPosition(x, y);
    }

    bool collidePaddle(const Paletka& p);

    void draw(sf::RenderTarget& target) const {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
    const sf::CircleShape& getShape() const { return shape; }

    void setPosition(float newX, float newY) {
        x = newX;
        y = newY;
        shape.setPosition(x, y);
    }

    void setVelocity(float newVx, float newVy) {
        vx = newVx;
        vy = newVy;
    }

    void setRadius(float newRadius) {
        radius = newRadius;
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
    }
};