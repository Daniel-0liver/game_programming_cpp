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
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window      *mWindow{};
    SDL_Renderer    *mRenderer{};
    bool            mIsRunning{true};
    Actor           mGreyWall{"GreyWall"};
    Actor           mGreenBlock{"GreenBlock"};
    Actor           mYellowParticle{"YellowParticle"};
    Actor           mInvisibleTemp{"InvisibleTemp"};
    Uint32          mTicksCount{0};
    float           mDeltaTime;
};

#endif // GAMEPROGRAMMINGCPP_CHAPTER02_GAME_H
