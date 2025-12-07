#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"
#include "GameState.h"

class Game {
private:
    static constexpr float W = 640.f;
    static constexpr float H = 480.f;

    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

    bool m_isGameSaved;
    float m_blockWidth;
    float m_blockHeight;

    void processEvents();
    void update(sf::Time dt);
    void render();

    void initBlocks();
    void createBlocksFromData(const std::vector<BlockData>& blocksData);

public:
    Game();
    Game(const std::string& saveFile);
    void run();

    void saveGame();
};