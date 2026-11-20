#include "Game.h"
#include "Component.h"
#include <algorithm>
#include <iostream>
#include <string>
bool Game::Initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << SDL_GetError() << '\n'; return false;
    }
    if (!SDL_CreateWindowAndRenderer("Exercicio 5", 960, 600, 0, &mWindow, &mRenderer)) {
        std::cerr << SDL_GetError() << '\n'; return false;
    }
    SDL_SetRenderVSync(mRenderer, 1);
    ResetScene();
    return true;
}
Game::~Game() {
    mActors.clear();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
void Game::ResetScene() {
    mActors.clear();
    mPaused = false;
    auto wall = std::make_unique<Actor>("Parede cinza", Vector2{480, 500});
    wall->AddComponent(std::make_unique<RectangleComponent>(wall.get(), 800, 30, SDL_Color{145, 150, 160, 255}));
    mActors.push_back(std::move(wall));
    auto block = std::make_unique<Actor>("Bloco verde", Vector2{80, 220});
    block->AddComponent(std::make_unique<MoveComponent>(block.get(), Vector2{65, 0}));
    block->AddComponent(std::make_unique<RectangleComponent>(block.get(), 70, 70, SDL_Color{70, 210, 120, 255}));
    mActors.push_back(std::move(block));
    auto particle = std::make_unique<Actor>("Particula amarela", Vector2{80, 380});
    particle->AddComponent(std::make_unique<MoveComponent>(particle.get(), Vector2{160, -40}));
    particle->AddComponent(std::make_unique<RectangleComponent>(particle.get(), 26, 26, SDL_Color{255, 215, 65, 255}));
    particle->AddComponent(std::make_unique<LifetimeComponent>(particle.get(), 2));
    mActors.push_back(std::move(particle));
    auto timer = std::make_unique<Actor>("Temporizador invisivel (3 segundos)");
    timer->AddComponent(std::make_unique<LifetimeComponent>(timer.get(), 3));
    mActors.push_back(std::move(timer));
    std::cout << "Cena reiniciada. Espaco: pausa | R: reinicia | Esc: sai\n";
}
void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) mRunning = false;
        if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
            if (event.key.key == SDLK_ESCAPE) mRunning = false;
            if (event.key.key == SDLK_R) ResetScene();
            if (event.key.key == SDLK_SPACE) {
                mPaused = !mPaused;
                for (const auto& actor : mActors)
                    if (actor->getState() != State::Dead)
                        actor->setState(mPaused ? State::Paused : State::Active);
            }
        }
    }
}
void Game::Draw() {
    SDL_SetRenderDrawColor(mRenderer, 22, 27, 38, 255);
    SDL_RenderClear(mRenderer);
    for (const auto& actor : mActors) actor->Draw(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 225, 230, 240, 255);
    SDL_RenderDebugText(mRenderer, 24, 24, "EXERCICIO 5 - ACTORS E COMPONENTS");
    SDL_RenderDebugText(mRenderer, 24, 50, "ESPACO: pausa | R: reinicia | ESC: sai");
    SDL_RenderDebugText(mRenderer, 24, 90, "Cinza: desenho | Verde: movimento + desenho");
    SDL_RenderDebugText(mRenderer, 24, 114, "Amarelo: movimento + desenho + vida de 2s");
    const std::string status = std::string(mPaused ? "PAUSADO" : "RODANDO") +
        " | Particula: " + (mActors[2]->getState() == State::Dead ? "morta" : "viva") +
        " | Timer invisivel: " + (mActors[3]->getState() == State::Dead ? "expirou" : "ativo");
    SDL_RenderDebugText(mRenderer, 24, 550, status.c_str());
    SDL_RenderPresent(mRenderer);
}
void Game::Run(float maxSeconds) {
    const Uint64 start = SDL_GetTicksNS();
    Uint64 previous = start;
    while (mRunning) {
        // Reset/input happens before calculating dt: reset frames begin at zero.
        ProcessInput();
        const Uint64 now = SDL_GetTicksNS();
        const float dt = std::min(static_cast<float>(now - previous) / 1.0e9f, 0.05f);
        previous = now;
        if (!mRunning) break;
        for (const auto& actor : mActors) actor->Update(dt);
        Draw();
        if (maxSeconds > 0 && static_cast<double>(now - start) / 1.0e9 >= maxSeconds) break;
        SDL_Delay(1);
    }
}
