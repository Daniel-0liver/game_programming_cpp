//
// Created by oliver on 07/11/26.
//

#include "Actor.h"
#include "Component.h"

Actor::Actor(std::string newName) : name(newName), mState(State::Active) {}

Actor::~Actor() = default;


Vector2 Actor::getPosition() const {
    return position;
}

void Actor::setPosition(const Vector2 &newPosition) {
    position = newPosition;
}

State Actor::getState() {
    return mState;
}

void Actor::setState(State state) {
    mState = state;
}

std::string Actor::getName() const {
    return name;
}

void Actor::Update(float deltaTime) {
    if (mState != State::Active) return;
    for (const auto &component : mComponents) {
        component->Update(deltaTime);
    }
}

void Actor::Draw(SDL_Renderer *render) const {
    if (mState == State::Dead) return;
    for (const auto &component : mComponents) {
        component->Draw(render);
    }
}

void Actor::AddComponent(std::unique_ptr<Component> component) {
    int myOrder = component->getUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter) {
        if (myOrder <  (*iter)->getUpdateOrder()) {
            break;
        }
    }
    mComponents.insert(iter, std::move(component));
}
