#include "Game/Game.hpp"

int main() {
    
    Game snakeGame;
    snakeGame.initialize();

    while (snakeGame.IsRunning()) {
        snakeGame.update();
        snakeGame.render();
    }

    snakeGame.shutdown();

    return 0;
}
