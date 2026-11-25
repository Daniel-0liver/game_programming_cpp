#include "Game.h"

#include "LifeTimeComponent.h"
#include "MoveComponent.h"
#include "RetangleComponent.h"
#include "SpawnerComponent.h"

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (!sdlResult) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        "Chapter 02",
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

    auto mParticleEmiter = std::make_unique<Actor>("ParticleEmiter");
    mParticleEmiter->AddComponent(std::make_unique<SpawnerComponent>(
        this,
        mParticleEmiter.get()
    ));
    AddActor(std::move(mParticleEmiter));

    auto mGreyWall = std::make_unique<Actor>("GreyWall");
    mGreyWall->setPosition({.x = 500.0f, .y = 650.0f});
    mGreyWall->AddComponent(std::make_unique<RetangleComponent>(
        mGreyWall.get(),
        650.0f,
        100.0f,
        SDL_Color{.r = 138, .g = 140, .b = 137, .a = 255}
    ));
    AddActor(std::move(mGreyWall));

    auto mGreenBlock = std::make_unique<Actor>("GreenBlock");
    mGreenBlock->setPosition({.x = 100.0f, .y = 80.0f});
    mGreenBlock->AddComponent(std::make_unique<RetangleComponent>(
        mGreenBlock.get(),
        100.0f,
        100.0f,
        SDL_Color{.r = 97, .g = 235, .b = 52, .a = 255}
    ));
    mGreenBlock->AddComponent(std::make_unique<MoveComponent>(
        mGreenBlock.get(),
        Vector2{.x = 100.0f, .y = 100.0f}
    ));
    AddActor(std::move(mGreenBlock));

    auto mInvisibleTemp = std::make_unique<Actor>("InvisibleTemp");
    mInvisibleTemp->AddComponent(std::make_unique<LifeTimeComponent>(
        mInvisibleTemp.get(),
        5.0f
    ));
    AddActor(std::move(mInvisibleTemp));

    return true;
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
    while (!(SDL_GetTicks() >= mTicksCount + 16)) {
    }

    mDeltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    if (mDeltaTime > 0.05f) {
        mDeltaTime = 0.05f;
    }

    UpdateActors();

    mTicksCount = SDL_GetTicks();
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 24, 27, 34, 255);
    SDL_RenderClear(mRenderer);

    DrawActors();

    SDL_RenderPresent(mRenderer);
}

void Game::Shutdown() const {
    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
    }
    if (mWindow) {
        SDL_DestroyWindow(mWindow);
    }
    SDL_Quit();
}

void Game::AddActor(std::unique_ptr<Actor> actor) {
    if (!mIsUpdating) {
        mActors.emplace_back(std::move(actor));
    } else {
        mPendingActors.emplace_back(std::move(actor));
    }
}

void Game::RemoveActor() {
    std::erase_if(mActors, [](const std::unique_ptr<Actor> &a) {
        return a->getState() == State::Dead;
    });
}

void Game::UpdateActors() {
    mIsUpdating = true;
    for (auto &actor: mActors) {
        actor->Update(mDeltaTime);
    }
    RemoveActor();
    for (auto &actor: mPendingActors) {
        mActors.emplace_back(std::move(actor));
    }
    mPendingActors.clear();
    mIsUpdating = false;
}

void Game::DrawActors() {
    for (const auto &actor: mActors) {
        actor->Draw(mRenderer);
    }
}

void Game::SpawnParticle() {
    auto mYellowParticle = std::make_unique<Actor>("YellowParticle");
    mYellowParticle->setPosition({.x = 150.0f, .y = 120.0f});
    mYellowParticle->AddComponent(std::make_unique<RetangleComponent>(
        mYellowParticle.get(),
        10.0f,
        10.0f,
        SDL_Color{.r = 207, .g = 207, .b = 54, .a = 255}
    ));
    mYellowParticle->AddComponent(std::make_unique<MoveComponent>(
        mYellowParticle.get(),
        Vector2{.x = 200.0f, .y = 0.0f}
    ));
    mYellowParticle->AddComponent(std::make_unique<LifeTimeComponent>(
        mYellowParticle.get(),
        2.0f
    ));
    AddActor(std::move(mYellowParticle));
}