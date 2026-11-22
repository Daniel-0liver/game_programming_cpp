#include "Game.h"
#include <iostream>

#include "Actor.h"
#include "MoveComponent.h"
#include "RetangleComponent.h"

int main(int argc, char* argv[]) {
    Game game;
    bool init = game.Initialize();
    if (!init) {
        std::cout << "Failed to initialize the game." << std::endl;
        return -1;
    } else {
        game.RunLoop();
    }
    game.Shutdown();
}
