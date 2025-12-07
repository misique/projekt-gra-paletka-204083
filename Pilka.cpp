#include "Pilka.h"
#include "Paletka.h"

bool Pilka::collidePaddle(const Paletka& p) {
    float palX = p.getX();
    float palY = p.getY();
    float palW = p.getSzerokosc();
    float palH = p.getWysokosc();

    bool wZakresieX = (x >= palX - palW / 2.f && x <= palX + palW / 2.f);
    bool dotykaZGory = (y + radius >= palY - palH / 2.f) && (y - radius < palY - palH / 2.f);

    if (wZakresieX && dotykaZGory) {
        vy = -std::abs(vy);
        y = (palY - palH / 2.f) - radius;
        shape.setPosition(x, y);
        return true;
    }
    return false;
}