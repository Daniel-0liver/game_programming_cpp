//
// Created by oliver on 29/10/26.
//

#ifndef GAMEPROGRAMMINGCPP_GAME_H
#define GAMEPROGRAMMINGCPP_GAME_H

#include <SDL3/SDL.h>

class Game {
public:
    Game();
    // Initialize the game in this case SDL
    bool Initialize();
    // Run the game loop until the game is over
    void RunLoop();
    // Free all the memory used by the game
    void Shutdown();
private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // Window created by SDL
    SDL_Window* mWindow;
    // Game should continue to run while this is true
    bool mIsRunning;
};


#endif //GAMEPROGRAMMINGCPP_GAME_H
