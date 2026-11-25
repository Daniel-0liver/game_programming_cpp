//
// Created by oliver on 24/11/26.
//

#include "../includes/SpawnerComponent.h"

SpawnerComponent::SpawnerComponent(Game *game, Actor *actor)
    : Component(actor), mGame(game) {}

void SpawnerComponent::Update(float deltaTime) {
    if (!mIsSpawning) {
        mGame->SpawnParticle();
    }
    mIsSpawning = true;
}
