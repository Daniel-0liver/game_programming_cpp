#ifndef GAMEPROGRAMMINGCPP_CHAPTER02_GAME_H
#define GAMEPROGRAMMINGCPP_CHAPTER02_GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Actor.h"

class Game {
public:
    bool Initialize();
    void RunLoop();
    void Shutdown() const;
    std::vector<std::unique_ptr<Actor>> mActors;
    std::vector<std::unique_ptr<Actor>> mPendingActors;
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    void AddActor(std::unique_ptr<Actor> actor);
    void RemoveActor();
    void UpdateActors();
    void DrawActors();

    SDL_Window      *mWindow{};
    SDL_Renderer    *mRenderer{};
    bool            mIsRunning{true};
    Uint32          mTicksCount{0};
    float           mDeltaTime{0.0f};
    bool            mIsUpdating{false};
};

#endif // GAMEPROGRAMMINGCPP_CHAPTER02_GAME_H
