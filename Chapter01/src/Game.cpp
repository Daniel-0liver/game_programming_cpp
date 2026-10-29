//
// Created by oliver on 29/10/26.
//

#include "Game.h"

Game::Game() : mWindow(nullptr), mIsRunning(true) {
    mWindow = SDL_CreateWindow(
            "Game Programming in C++ (Chapter 1)",
            1024,
            768,
            0
    );
}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);


    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::Shutdown() {
    if (mWindow) {
        SDL_DestroyWindow(mWindow);
    }
    SDL_Quit();
}

void Game::RunLoop() {
    ProcessInput();
    UpdateGame();
    GenerateOutput();
}

void Game::ProcessInput() {

}

void Game::UpdateGame() {

}

void Game::GenerateOutput() {

}