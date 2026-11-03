//
// Created by oliver on 02/11/26.
//

#include "../includes/Ball.h"

Ball::Ball(Vector2 position, Vector2 velocity)
    : mPosition(position), mVelocity(velocity) {
}

bool Ball::Update(float deltaTime,
                  const Vector2& paddleOnePosition,
                  const Vector2& paddleTwoPosition,
                  float paddleHeight) {
    mPosition.x += mVelocity.x * deltaTime;
    mPosition.y += mVelocity.y * deltaTime;

    const bool hitsPaddleOne =
        mPosition.y > paddleOnePosition.y &&
        mPosition.y < paddleOnePosition.y + paddleHeight;
    const bool hitsPaddleTwo =
        mPosition.y > paddleTwoPosition.y &&
        mPosition.y < paddleTwoPosition.y + paddleHeight;

    if (hitsPaddleOne && mPosition.x <= THICKNESS && mVelocity.x < 0.0f) {
        mVelocity.x *= -1.0f;
    }

    if (hitsPaddleTwo && mPosition.x >= 1024.0f - THICKNESS &&
        mVelocity.x > 0.0f) {
        mVelocity.x *= -1.0f;
    }

    if (mPosition.x <= 0.0f || mPosition.x >= 1024.0f) {
        return false;
    }

    if (mPosition.y <= THICKNESS && mVelocity.y < 0.0f) {
        mPosition.y = THICKNESS;
        mVelocity.y *= -1.0f;
    } else if (mPosition.y >= 768.0f - THICKNESS && mVelocity.y > 0.0f) {
        mPosition.y = 768.0f - THICKNESS;
        mVelocity.y *= -1.0f;
    }

    return true;
}

void Ball::Draw(SDL_Renderer* renderer) const {
    const SDL_FRect ball{
        .x = mPosition.x - THICKNESS / 2.0f,
        .y = mPosition.y - THICKNESS / 2.0f,
        .w = THICKNESS,
        .h = THICKNESS
    };
    SDL_RenderFillRect(renderer, &ball);
}
