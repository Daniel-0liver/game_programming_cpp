//
// Created by oliver on 21/11/26.
//

#include "../includes/PositionLogComponent.h"

PositionLogComponent::PositionLogComponent(Actor *actor)
    : Component(actor, 200) {}

void PositionLogComponent::Update(float deltaTime) {
    Vector2 position = mActor->GetPosition();
    std::cout << mActor->getName() << " log de Posição: (" << position.x << ", " << position.y << ")" << std::endl;
}
