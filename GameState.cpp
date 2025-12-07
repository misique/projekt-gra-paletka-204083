#include "GameState.h"
#include <fstream>
#include <iostream>

void GameState::capture(float paddleX, float paddleY,
    float ballX, float ballY, float ballVx, float ballVy,
    const std::vector<BlockData>& stonesData) {
    paddlePosition.x = paddleX;
    paddlePosition.y = paddleY;

    ballPosition.x = ballX;
    ballPosition.y = ballY;
    ballVelocity.x = ballVx;
    ballVelocity.y = ballVy;

    blocks = stonesData;
}

bool GameState::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku " << filename << " do zapisu\n";
        return false;
    }

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";
    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    std::cout << "Zapisano gre do: " << filename << " (" << blocks.size() << " blokow)\n";
    return true;
}

bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku " << filename << " do odczytu\n";
        return false;
    }

    std::string label;

    if (!(file >> label >> paddlePosition.x >> paddlePosition.y) || label != "PADDLE") {
        std::cerr << "Blad formatu pliku: PADDLE\n";
        return false;
    }

    if (!(file >> label >> ballPosition.x >> ballPosition.y
        >> ballVelocity.x >> ballVelocity.y) || label != "BALL") {
        std::cerr << "Blad formatu pliku: BALL\n";
        return false;
    }

    int blocksCount;
    if (!(file >> label >> blocksCount) || label != "BLOCKS_COUNT") {
        std::cerr << "Blad formatu pliku: BLOCKS_COUNT\n";
        return false;
    }

    blocks.clear();
    blocks.reserve(blocksCount);

    for (int i = 0; i < blocksCount; ++i) {
        BlockData data;
        if (!(file >> data.x >> data.y >> data.hp)) {
            std::cerr << "Blad podczas wczytywania bloku " << i << "\n";
            return false;
        }
        blocks.push_back(data);
    }

    file.close();
    std::cout << "Wczytano stan gry z " << filename
        << " (" << blocks.size() << " blokow)\n";
    return true;
}