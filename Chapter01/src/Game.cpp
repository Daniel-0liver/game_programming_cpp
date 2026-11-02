//
// Created by oliver on 29/10/26.
//

#include "Game.h"

Game::Game() : mWindow(nullptr),
               mIsRunning(true),
               mRenderer(nullptr),
               mTicksCount(0),
               mPaddleDir(0),
               paddleH(100) {
    mBallPos.x = 1024.0f / 2.0f;
    mBallPos.y = 768.0f / 2.0f;
    mBallVel.x = -300.0f;
    mBallVel.y = 300.0f;
    mPaddlePos.x = 0.0f;
    mPaddlePos.y = 768.0f / 2.0f;
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

    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        mPaddleDir -= 1;
    }

    if (state[SDL_SCANCODE_S]) {
        mPaddleDir += 1;
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
    if (mPaddleDir != 0) {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

        // Bound the paddle position to the screen
        if (mPaddlePos.y <= THICKNESS) {
            mPaddlePos.y = THICKNESS;
        }
        if (mPaddlePos.y >= (768 - THICKNESS) - paddleH) {
            mPaddlePos.y = (768 - THICKNESS) - paddleH;
        }
    }

    // Update the ticks count to the current frame
    mTicksCount = SDL_GetTicks();

    // Update ball position based in its velocity
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    // Bounce if needed
    // Did we intersect with the paddle?
    float diff = mPaddlePos.y - mBallPos.y;
    // Take absolute value of difference
    diff = (diff > 0.0f) ? diff : -diff;
    if (
        // Our y-difference is small enough
        diff <= paddleH / 2.0f &&
        // We are in the correct x-position
        mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
        // The ball is moving to the left
        mBallVel.x < 0.0f)
    {
        mBallVel.x *= -1.0f;
    }
    // Did the ball go off the screen? (if so, end game)
    else if (mBallPos.x <= 0.0f)
    {
        mIsRunning = false;
    }
    // Did the ball collide with the right wall?
    else if (mBallPos.x >= (1024.0f - THICKNESS) && mBallVel.x > 0.0f)
    {
        mBallVel.x *= -1.0f;
    }

    // Did the ball collide with the top wall?
    if (mBallPos.y <= THICKNESS && mBallVel.y < 0.0f)
    {
        mBallVel.y *= -1;
    }
    // Did the ball collide with the bottom wall?
    else if (mBallPos.y >= (768 - THICKNESS) &&
        mBallVel.y > 0.0f)
    {
        mBallVel.y *= -1;
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

    // Draw a wall on the right of the screen
    drawWall(mRenderer, 1024 - THICKNESS, 0, THICKNESS, 768);

    // Draw the paddle
    SDL_FRect paddle{
        .x = (mPaddlePos.x),
        .y = (mPaddlePos.y),
        .w = THICKNESS,
        .h = paddleH
    };

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    SDL_RenderFillRect(mRenderer, &paddle);

    // Draw the ball
    SDL_FRect ball{
        .x = (mBallPos.x - THICKNESS / 2.0f),
        .y = (mBallPos.y - THICKNESS / 2.0f),
        .w = THICKNESS,
        .h = THICKNESS
    };

    SDL_RenderFillRect(mRenderer, &ball);

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
