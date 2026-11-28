#ifndef GAMEPROGRAMMINGCPP_CHAPTER02_GAME_H
#define GAMEPROGRAMMINGCPP_CHAPTER02_GAME_H

#include <SDL3/SDL.h>

#include "Actor.h"

class Game {
public:
    bool Initialize();

    void RunLoop();

    void Shutdown() const;

    void SpawnParticle();

private:
    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    void AddActor(std::unique_ptr<Actor> actor);

    void RemoveActor();

    void UpdateActors();

    void DrawActors();

    SDL_Window *mWindow{};
    SDL_Renderer *mRenderer{};
    SDL_Texture *mCharacter{};
    bool mIsRunning{true};
    Uint32 mTicksCount{0};
    float mDeltaTime{0.0f};
    bool mIsUpdating{false};
    std::vector<std::unique_ptr<Actor> > mActors;
    std::vector<std::unique_ptr<Actor> > mPendingActors;
};

#endif // GAMEPROGRAMMINGCPP_CHAPTER02_GAME_H