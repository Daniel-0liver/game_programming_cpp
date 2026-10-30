//
// Created by oliver on 29/10/26.
//

#include "Game.h"

Game::Game() : mWindow(nullptr), mIsRunning(true), mRenderer(nullptr) {
}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (!sdlResult) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        "Game Programming in C++ (Chapter 1)",
        1024,
        768,
        0
    );

    mRenderer = SDL_CreateRenderer(
        mWindow,
        nullptr
    );

    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::Shutdown() const {
    if (mWindow) {
        SDL_DestroyWindow(mWindow);
    }
    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
    }
    SDL_Quit();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    const bool *state = SDL_GetKeyboardState(nullptr);

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                mIsRunning = false;
                break;
            default: ;
        }
    }

    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
}

void Game::UpdateGame() {
}

void Game::GenerateOutput() {

    // Set the color that will be drawn to the screen (RGBA)
    SDL_SetRenderDrawColor(
        mRenderer,
        0,
        0,
        255,
        255
    );

    // Clear the back buffer to the color set above
    SDL_RenderClear(mRenderer);

    // Swap the front and back buffers
    SDL_RenderPresent(mRenderer);
}
