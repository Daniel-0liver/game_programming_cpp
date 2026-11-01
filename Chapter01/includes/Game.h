//
// Created by oliver on 29/10/26.
//

#ifndef GAMEPROGRAMMINGCPP_GAME_H
#define GAMEPROGRAMMINGCPP_GAME_H
#include <iostream>

#include <SDL3/SDL.h>
#define THICKNESS 15

struct Vector2 {
    float x;
    float y;
};

class Game {
public:
    Game();

    // Initialize the game in this case SDL
    bool Initialize();

    // Run the game loop until the game is over
    void RunLoop();

    // Free all the memory used by the game
    void Shutdown() const;

    // Draw a wall to the screen
    static void drawWall(SDL_Renderer *renderer,
                         float x,
                         float y,
                         float width,
                         float height
    );

    Vector2 mPaddlePos;
    Vector2 mBallPos;
    Uint32 mTicksCount;
    int mPaddleDir;
    float paddleH;

private:
    // Helper functions for the game loop
    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    // Window created by SDL
    SDL_Window *mWindow;

    // Renderer created by SDL
    SDL_Renderer *mRenderer;

    // Game should continue to run while this is true
    bool mIsRunning;
};


#endif //GAMEPROGRAMMINGCPP_GAME_H
