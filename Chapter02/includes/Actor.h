//
// Created by oliver on 07/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_ACTOR_H
#define GAMEPROGRAMMINGCPP_ACTOR_H

#include <vector>
#include <memory>
#include <iostream>
#include <SDL3/SDL.h>

class Component;

struct Vector2 {
    float x;
    float y;
};

enum class State {
    Active,
    Paused,
    Dead
};

class Actor {
private:
    Vector2 position;
    std::string name;
    std::vector<std::unique_ptr<Component>> mComponents;
    State mState;
public:
    Actor(std::string newName);
    ~Actor();

    Vector2 getPosition() const;

    std::string getName() const;

    void setPosition(const Vector2 &newPosition);
    void setState(State state);

    void Update(float deltaTime);
    void Draw(SDL_Renderer *render) const;
    void AddComponent(std::unique_ptr<Component> component);
};

#endif //GAMEPROGRAMMINGCPP_ACTOR_H
