#include "Game.h"
#include <cstdlib>
#include <string_view>
int main(int argc, char* argv[]) {
    Game game;
    if (!game.Initialize()) return 1;
    // Bounded run for smoke testing, e.g. Chapter02 --seconds 4
    float seconds = 0;
    if (argc == 3 && std::string_view(argv[1]) == "--seconds")
        seconds = std::strtof(argv[2], nullptr);
    game.Run(seconds);
    return 0;
}
