//
// Created by oliver on 07/11/26.
//

#include "Actor.h"

#include <algorithm>

Actor::Actor(Game *game)
    : mState(EActive),
    mGame(game),
    mPosition(Vector2::Zero),
    mScale(1.0f),
    mRotation(0.0f)
{
    mGame->AddActor(this);
}

Actor::~Actor() = default;

Vector2 Actor::GetPosition() const {
    return mPosition;
}

void Actor::SetPosition(const Vector2 &newPosition) {
    mPosition = newPosition;
}

float Actor::GetScale() const {
    return mScale;
}

void Actor::SetScale(float newScale) {
    mScale = newScale;
}

float Actor::GetRotation() const {
    return mRotation;
}

void Actor::SetRotation(float newRotation) {
    mRotation = newRotation;
}

Actor::State Actor::GetState() const {
    return mState;
}

void Actor::SetState(State state) {
    mState = state;
}

Game *Actor::GetGame() {
    return mGame;
}

void Actor::Update(float deltaTime) {
    if (mState == EActive) {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (auto comp : mComponents) {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {

}

void Actor::AddComponent(Component *component) {
    int myOrder = component->getUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter) {
        if (myOrder <  (*iter)->getUpdateOrder()) {
            break;
        }
    }
    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component *component) {
    auto iter = std::find(
        mComponents.begin(),
        mComponents.end(),
        component
    );
    if (iter != mComponents.end()) {
        mComponents.erase(iter);
    }
}
