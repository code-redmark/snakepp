#pragma once

#include "../Renderer/Renderer.hpp"

 class Game {
    private:
        bool isRunning;
        Renderer renderer;

    public:
        Game();
        void initialize();

        void update();
        void render();

        bool IsRunning() const;

        void shutdown() {
            
        }
};