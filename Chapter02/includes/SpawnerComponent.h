//
// Created by oliver on 24/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_SPAWNERCOMPONENT_H
#define GAMEPROGRAMMINGCPP_SPAWNERCOMPONENT_H
#include "Component.h"
#include "Game.h"

class SpawnerComponent : public Component {
protected:
    bool mIsSpawning{false};
    Game *mGame;
public:
    SpawnerComponent(Game *game, Actor *actor);
    void Update(float) override;
};


#endif //GAMEPROGRAMMINGCPP_SPAWNERCOMPONENT_H
