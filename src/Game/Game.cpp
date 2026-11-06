#include "Game.hpp"

Game::Game() : isRunning(true) {}

void Game::initialize() {
    renderer.initialize(800.f, 600.f);
    isRunning = true;
}

void Game::update() {
    // Metti qui il codice per aggiornare lo stato del gioco, come la logica del gioco, il movimento del serpente, 
    // la gestione delle collisioni, ecc.
}

void Game::render() {
    isRunning = renderer.render();
}

bool Game::IsRunning() const {
    return isRunning;
}