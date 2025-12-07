#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <string>

struct BlockData {
    float x, y;
    int hp;
};

class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    GameState() = default;

    void capture(float paddleX, float paddleY,
        float ballX, float ballY, float ballVx, float ballVy,
        const std::vector<BlockData>& stonesData);

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    const sf::Vector2f& getPaddlePosition() const { return paddlePosition; }
    const sf::Vector2f& getBallPosition() const { return ballPosition; }
    const sf::Vector2f& getBallVelocity() const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }
    void setBlocks(const std::vector<BlockData>& newBlocks) { blocks = newBlocks; }
};