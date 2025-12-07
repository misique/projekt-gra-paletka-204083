#include "Game.h"
#include <iostream>

Game::Game()
    : m_window(sf::VideoMode(W, H), "Arkanoid"),
    m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
    m_pilka(320.f, 300.f, 4.f, 3.f, 8.f),
    m_isGameSaved(false),
    m_blockWidth(0.f),
    m_blockHeight(0.f)
{
    m_window.setFramerateLimit(60);
    initBlocks();
}

Game::Game(const std::string& saveFile)
    : m_window(sf::VideoMode(W, H), "Arkanoid - Wczytana gra"),
    m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
    m_pilka(320.f, 300.f, 4.f, 3.f, 8.f),
    m_isGameSaved(false),
    m_blockWidth(0.f),
    m_blockHeight(0.f)
{
    m_window.setFramerateLimit(60);

    GameState state;
    if (state.loadFromFile(saveFile)) {

        sf::Vector2f paddlePos = state.getPaddlePosition();
        m_paletka.setPosition(paddlePos.x, paddlePos.y);

        sf::Vector2f ballPos = state.getBallPosition();
        sf::Vector2f ballVel = state.getBallVelocity();
        m_pilka.setPosition(ballPos.x, ballPos.y);
        m_pilka.setVelocity(ballVel.x, ballVel.y);

        createBlocksFromData(state.getBlocks());
    }
    else {
        std::cout << "Nie mozna wczytac zapisu. Rozpoczynam nowa gre.\n";
        initBlocks();
    }
}

void Game::initBlocks()
{
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float Przerwa = 2.f;
    m_blockHeight = 25.f;
    m_blockWidth = (W - (ILOSC_KOLUMN - 1) * Przerwa) / ILOSC_KOLUMN;

    m_bloki.clear();
    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (m_blockWidth + Przerwa);
            float posY = 50.f + y * (m_blockHeight + Przerwa);

            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(m_blockWidth, m_blockHeight),
                L
            );
        }
    }
}

void Game::createBlocksFromData(const std::vector<BlockData>& blocksData)
{
    const int ILOSC_KOLUMN = 6;
    const float Przerwa = 2.f;
    m_blockHeight = 25.f;
    m_blockWidth = (W - (ILOSC_KOLUMN - 1) * Przerwa) / ILOSC_KOLUMN;

    m_bloki.clear();

    for (const auto& blockData : blocksData) {
        Stone stone = Stone::createFromData(
            blockData.x,
            blockData.y,
            m_blockWidth,
            m_blockHeight,
            blockData.hp
        );
        m_bloki.push_back(stone);
    }

    std::cout << "Utworzono " << m_bloki.size() << " blokow z danych\n";
}

void Game::run()
{
    while (m_window.isOpen()) {
        sf::Time dt = m_deltaClock.restart();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            m_window.close();

        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::F5) {
            saveGame();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight();

    m_paletka.clampToBounds(W);
}

void Game::update(sf::Time)
{
    m_pilka.move();
    m_pilka.collideWalls(W, H);
    m_pilka.collidePaddle(m_paletka);

    sf::FloatRect pilRect(
        m_pilka.getX() - m_pilka.getRadius(),
        m_pilka.getY() - m_pilka.getRadius(),
        m_pilka.getRadius() * 2,
        m_pilka.getRadius() * 2
    );

    for (auto& b : m_bloki) {
        if (b.isDestroyed()) continue;

        if (b.getGlobalBounds().intersects(pilRect)) {
            b.hit();
            m_pilka.bounceY();
            break;
        }
    }

    if (m_pilka.getY() > H) {
        std::cout << "Koniec gry!\n";
        m_window.close();
    }
}

void Game::render()
{
    m_window.clear(sf::Color(30, 30, 40));

    m_paletka.draw(m_window);
    m_pilka.draw(m_window);

    for (auto& b : m_bloki)
        if (!b.isDestroyed()) m_window.draw(b);

    m_window.display();
}

void Game::saveGame()
{
    std::vector<BlockData> blocksData;
    for (const auto& stone : m_bloki) {
        BlockData data;
        sf::Vector2f pos = stone.getPos();
        data.x = pos.x;
        data.y = pos.y;
        data.hp = stone.getHP(); 
        blocksData.push_back(data);
    }

    GameState state;
    state.capture(
        m_paletka.getX(), m_paletka.getY(), 
        m_pilka.getX(), m_pilka.getY(), m_pilka.getVx(), m_pilka.getVy(), 
        blocksData
    );

    if (state.saveToFile("savegame.txt")) {
        m_isGameSaved = true;
        std::cout << "Gra zapisana pomyslnie!\n";
    }
}