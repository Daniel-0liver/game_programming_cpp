#include "Component.h"
#include <iostream>
void MoveComponent::Update(float deltaTime) {
    auto position = mActor->getPosition();
    position.x += mVelocity.x * deltaTime;
    position.y += mVelocity.y * deltaTime;
    mActor->setPosition(position);
}
void LifetimeComponent::Update(float deltaTime) {
    mRemaining -= deltaTime;
    if (mRemaining <= 0.0f) {
        mActor->setState(State::Dead);
        std::cout << mActor->getName() << ": tempo de vida encerrado.\n";
    }
}
void RectangleComponent::Draw(SDL_Renderer* renderer) const {
    const auto position = mActor->getPosition();
    const SDL_FRect rect{position.x - mWidth / 2, position.y - mHeight / 2,
                         mWidth, mHeight};
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
    SDL_RenderFillRect(renderer, &rect);
}
