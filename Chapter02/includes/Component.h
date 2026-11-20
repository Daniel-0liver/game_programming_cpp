#pragma once
#include "Actor.h"
class Component {
public:
    explicit Component(Actor* actor, int updateOrder = 100)
        : mActor(actor), mUpdateOrder(updateOrder) {}
    virtual ~Component() = default;
    int getUpdateOrder() const { return mUpdateOrder; }
    virtual void Update(float) {}
    virtual void Draw(SDL_Renderer*) const {}
protected:
    Actor* mActor; // Non-owning: the actor owns this component.
private:
    int mUpdateOrder;
};
class MoveComponent : public Component {
public:
    MoveComponent(Actor* actor, Vector2 velocity)
        : Component(actor), mVelocity(velocity) {}
    void Update(float deltaTime) override;
private:
    Vector2 mVelocity;
};
class LifetimeComponent : public Component {
public:
    LifetimeComponent(Actor* actor, float seconds)
        : Component(actor, 200), mRemaining(seconds) {}
    void Update(float deltaTime) override;
private:
    float mRemaining;
};
class RectangleComponent : public Component {
public:
    RectangleComponent(Actor* actor, float width, float height, SDL_Color color)
        : Component(actor), mWidth(width), mHeight(height), mColor(color) {}
    void Draw(SDL_Renderer* renderer) const override;
private:
    float mWidth, mHeight;
    SDL_Color mColor;
};
