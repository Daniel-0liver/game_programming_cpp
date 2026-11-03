//
// Created by oliver on 02/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_BALL_H
#define GAMEPROGRAMMINGCPP_BALL_H

#include <SDL3/SDL.h>

constexpr float THICKNESS = 15.0f;

struct Vector2 {
    float x;
    float y;
};

class Ball final {
public:
    Ball(Vector2 position = {1024.0f / 2.0f, 768.0f / 2.0f},
         Vector2 velocity = {-200.0f, 200.0f});

    // Returns false when the ball leaves the play area.
    bool Update(float deltaTime,
                const Vector2& paddleOnePosition,
                const Vector2& paddleTwoPosition,
                float paddleHeight);
    void Draw(SDL_Renderer* renderer) const;

    const Vector2& Position() const { return mPosition; }

private:
    Vector2 mPosition;
    Vector2 mVelocity;
};


#endif //GAMEPROGRAMMINGCPP_BALL_H
