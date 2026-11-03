//
// Created by oliver on 29/10/26.
//

#include "Game.h"

Game::Game() : mWindow(nullptr),
               mIsRunning(true),
               mRenderer(nullptr),
               mTicksCount(0),
               mPaddleOneDir(0),
               mPaddleTwoDir(0),
               paddleH(100) {
    mPaddleOnePos.x = 0.0f;
    mPaddleOnePos.y = 768.0f / 2.0f;
    mPaddleTwoPos.x = 1024.0f - THICKNESS;
    mPaddleTwoPos.y = 768.0f / 2.0f;
    AddBall({1024.0f / 2.0f, 768.0f / 2.0f}, {-200.0f, 200.0f});
    AddBall({1024.0f / 2.0f, 768.0f / 2.0f}, {200.0f, -200.0f});
}

void Game::AddBall(Vector2 position, Vector2 velocity) {
    mBalls.emplace_back(position, velocity);
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

    mPaddleOneDir = 0;
    mPaddleTwoDir = 0;
    if (state[SDL_SCANCODE_W]) {
        mPaddleOneDir -= 1;
    }

    if (state[SDL_SCANCODE_S]) {
        mPaddleOneDir += 1;
    }

    if (state[SDL_SCANCODE_UP]) {
        mPaddleTwoDir -= 1;
    }

    if (state[SDL_SCANCODE_DOWN]) {
        mPaddleTwoDir += 1;
    }
}

void Game::UpdateGame() {
    // Wait until 16ms has elapsed since the last frame
    while (!(SDL_GetTicks() >= mTicksCount + 16)) {
    }

    // Delta time is the difference in ticks from the last frame to this frame
    // We need to convert it to seconds to convert milliseconds to seconds
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    // Clamp the maximum delta time value to 0.05 seconds
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    // Update the paddle position based on the direction and speed
    if (mPaddleOneDir != 0) {
        mPaddleOnePos.y += mPaddleOneDir * 300.0f * deltaTime;

        // Bound the paddle position to the screen
        if (mPaddleOnePos.y <= THICKNESS) {
            mPaddleOnePos.y = THICKNESS;
        }
        if (mPaddleOnePos.y >= (768 - THICKNESS) - paddleH) {
            mPaddleOnePos.y = (768 - THICKNESS) - paddleH;
        }
    }

    if (mPaddleTwoDir != 0) {
        mPaddleTwoPos.y += mPaddleTwoDir * 300.0f * deltaTime;

        // Bound the paddle position to the screen
        if (mPaddleTwoPos.y <= THICKNESS) {
            mPaddleTwoPos.y = THICKNESS;
        }
        if (mPaddleTwoPos.y >= (768 - THICKNESS) - paddleH) {
            mPaddleTwoPos.y = (768 - THICKNESS) - paddleH;
        }
    }

    // Update the ticks count to the current frame
    mTicksCount = SDL_GetTicks();

    for (auto ball = mBalls.begin(); ball != mBalls.end();) {
        if (!ball->Update(deltaTime, mPaddleOnePos, mPaddleTwoPos, paddleH)) {
            ball = mBalls.erase(ball);
        } else {
            ++ball;
        }
    }

    if (mBalls.empty()) {
        mIsRunning = false;
    }
}

void Game::GenerateOutput() {
    // Set the color that will be drawn to the screen (RGBA)
    SDL_SetRenderDrawColor(
        mRenderer,
        100,
        0,
        150,
        200
    );

    // Clear the back buffer to the color set above
    SDL_RenderClear(mRenderer);

    // Draw a wall at the top of the screen
    drawWall(mRenderer, 0, 0, 1024, THICKNESS);

    // Draw a wall at the bottom of the screen
    drawWall(mRenderer, 0, 768 - THICKNESS, 1024, THICKNESS);

    // Draw the paddleOne
    SDL_FRect paddleOne{
        .x = (mPaddleOnePos.x),
        .y = (mPaddleOnePos.y),
        .w = THICKNESS,
        .h = paddleH
    };

    // Draw the paddleTwo
    SDL_FRect paddleTwo{
        .x = (mPaddleTwoPos.x),
        .y = (mPaddleTwoPos.y),
        .w = THICKNESS,
        .h = paddleH
    };

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    SDL_RenderFillRect(mRenderer, &paddleOne);
    SDL_RenderFillRect(mRenderer, &paddleTwo);

    for (const Ball& ball : mBalls) {
        ball.Draw(mRenderer);
    }

    // Swap the front and back buffers
    SDL_RenderPresent(mRenderer);
}

void Game::drawWall(SDL_Renderer *renderer,
                    float x,
                    float y,
                    float width,
                    float height
) {
    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255
    );

    const SDL_FRect wall = {
        .x = x,
        .y = y,
        .w = width,
        .h = height
    };

    SDL_RenderFillRect(renderer, &wall);
}
