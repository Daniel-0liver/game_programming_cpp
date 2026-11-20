#pragma once
#include "Actor.h"
class Game {
public:
    ~Game();
    bool Initialize();
    void Run(float maxSeconds = 0);
private:
    void ResetScene();
    void ProcessInput();
    void Draw();
    SDL_Window* mWindow{};
    SDL_Renderer* mRenderer{};
    bool mRunning{true};
    bool mPaused{};
    std::vector<std::unique_ptr<Actor>> mActors;
};
