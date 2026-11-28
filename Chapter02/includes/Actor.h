//
// Created by oliver on 07/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_ACTOR_H
#define GAMEPROGRAMMINGCPP_ACTOR_H

#include <vector>
#include <Math.h>
#include "Component.h"


class Game;
class Component;

class Actor {
public:
    enum State {
        EActive,
        EPause,
        EDead
    };

    Actor(Game *game);

    virtual ~Actor();

    void Update(float deltaTime);

    void UpdateComponents(float deltaTime);

    virtual void UpdateActor(float deltaTime);

    void AddComponent(Component *component);

    void RemoveComponent(Component *component);

    Vector2 GetPosition() const;

    void SetPosition(const Vector2 &newPosition);

    float GetScale() const;

    void SetScale(float newScale);

    float GetRotation() const;

    void SetRotation(float newRotation);

    State GetState() const;

    void SetState(State state);

    Game *GetGame();

private:
    Vector2 mPosition;
    float mScale;
    float mRotation;
    std::vector<Component *> mComponents;
    State mState;
    Game *mGame;
};

#endif //GAMEPROGRAMMINGCPP_ACTOR_H
