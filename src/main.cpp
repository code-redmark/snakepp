#include "Game/Game.hpp"

#include <iostream>

int main() {
    
    try {
        Game snakeGame;
        snakeGame.initialize();

        while (snakeGame.IsRunning()) {
            snakeGame.update();
            snakeGame.render();
        }

        snakeGame.shutdown();

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
