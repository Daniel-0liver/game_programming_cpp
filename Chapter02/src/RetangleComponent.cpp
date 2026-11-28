//
// Created by oliver on 21/11/26.
//

#include "../includes/RetangleComponent.h"

#include "Actor.h"

RetangleComponent::RetangleComponent(Actor *actor, float newWidth, float newHeight, SDL_Color newColor, SDL_Texture *texture)
    : Component(actor, 200), width(newWidth), height(newHeight), color(newColor), mText(texture) {}

void RetangleComponent::Draw(SDL_Renderer *render) const {
    Vector2 position = mActor->GetPosition();
    const SDL_FRect rect = {.x = position.x - width / 2.0f, .y = position.y - height / 2.0f, .w = width, .h = height};
    SDL_RenderTexture(
            render,
            mText,
            nullptr,
            &rect
    );
}
