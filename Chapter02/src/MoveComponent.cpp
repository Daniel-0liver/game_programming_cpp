//
// Created by oliver on 21/11/26.
//

#include "../includes/MoveComponent.h"

MoveComponent::MoveComponent(Actor *actor, const Vector2 &velocity)
    : Component(actor, 100), mVelocity(velocity) {}

void MoveComponent::Update(float deltaTime) {
    Vector2 position = mActor->GetPosition();
    position.x += mVelocity.x * deltaTime;
    position.y += mVelocity.y * deltaTime;
    mActor->SetPosition(position);
}
