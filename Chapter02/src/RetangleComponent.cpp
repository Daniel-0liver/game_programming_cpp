//
// Created by oliver on 21/11/26.
//

#include "../includes/RetangleComponent.h"

#include "Actor.h"

RetangleComponent::RetangleComponent(Actor *actor, float newWidth, float newHeight, SDL_Color newColor)
    : Component(actor, 200), width(newWidth), height(newHeight), color(newColor) {}

void RetangleComponent::Draw(SDL_Renderer *render) const {
    Vector2 position = mActor->getPosition();
    const SDL_FRect rect = {.x = position.x - width / 2.0f, .y = position.y - height / 2.0f, .w = width, .h = height};
    SDL_SetRenderDrawColor(render ,color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(render, &rect);
}
