#include "Actor.h"
#include "Component.h"
#include <algorithm>
#include <utility>
Actor::Actor(std::string name, Vector2 position)
    : mName(std::move(name)), mPosition(position) {}
Actor::~Actor() = default;
void Actor::AddComponent(std::unique_ptr<Component> component) {
    mComponents.push_back(std::move(component));
    std::stable_sort(mComponents.begin(), mComponents.end(),
        [](const auto& a, const auto& b) {
            return a->getUpdateOrder() < b->getUpdateOrder();
        });
}
void Actor::Update(float deltaTime) {
    if (mState != State::Active) return;
    for (const auto& component : mComponents) component->Update(deltaTime);
}
void Actor::Draw(SDL_Renderer* renderer) const {
    if (mState == State::Dead) return;
    for (const auto& component : mComponents) component->Draw(renderer);
}
