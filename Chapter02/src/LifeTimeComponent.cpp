//
// Created by oliver on 22/11/26.
//

#include "../includes/LifeTimeComponent.h"

#include "Actor.h"

float LifeTimeComponent::getLifeTime() const {
    return mLifeTime;
}

LifeTimeComponent::LifeTimeComponent(Actor *actor, float lifeTime)
    : Component(actor), mLifeTime(lifeTime) {}

void LifeTimeComponent::Update(float deltaTime) {
    mLifeTime -= deltaTime;
    if (mLifeTime <= 0.0f) {
        mActor->SetState(State::Dead);
        SDL_Log(std::string("Actor " + mActor->getName() + " is dead.").c_str());
    }
}
