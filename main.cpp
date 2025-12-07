#include "Game.h"
#include "Menu.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid - Menu");
    Menu menu(window.getSize().x, window.getSize().y);

    bool inMenu = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (inMenu) {
                    if (event.key.code == sf::Keyboard::Up) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(150));
                        menu.przesunG();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(150));
                        menu.przesunD();
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int selection = menu.getSelectedItem();

                        if (selection == 0) { 
                            std::cout << "=== NOWA GRA ===\n";
                            inMenu = false;
                            window.setVisible(false);

                            Game game;
                            game.run();

                            window.setVisible(true);
                            inMenu = true;
                            std::cout << "=== POWROT DO MENU ===\n";
                        }
                        else if (selection == 1) { 
                            std::cout << "=== Wczytywanie gry ===\n";
                            inMenu = false;
                            window.setVisible(false);

                            Game game("savegame.txt");
                            game.run();

                            window.setVisible(true);
                            inMenu = true;
                            std::cout << "=== POWROT DO MENU ===\n";
                        }
                        else if (selection == 2) { 
                            std::cout << "Ostatnie wyniki...\n";
                            std::cout << "1. Gracz1: 1500 pkt\n";
                            std::cout << "2. Gracz2: 1200 pkt\n";
                            std::cout << "3. Gracz3: 800 pkt\n";
                        }
                        else if (selection == 3) { 
                            window.close();
                        }
                    }
                }
            }
        }

        if (inMenu) {
            window.clear(sf::Color(30, 30, 50));
            menu.draw(window);
            window.display();
        }
    }

    return 0;
}